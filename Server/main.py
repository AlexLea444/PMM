#!/usr/bin/env python3
import time
from http.server import HTTPServer
import paho.mqtt.client as mqtt 
import time
from flask import Flask, request, jsonify, Response
import os
from http.server import BaseHTTPRequestHandler
from routes.main import routes
from response.staticHandler import StaticHandler
from response.templateHandler import TemplateHandler
from response.badRequestHandler import BadRequestHandler
import threading

# Replace this with your own IP address
broker_address='10.5.15.62'

# Initiate client
client = mqtt.Client("Eddy") 
client.connect(broker_address)

# Define port and host
HOST_NAME = '127.0.0.1'
PORT_NUMBER = 8000

# Web page code
page = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PMM Remote Control System</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f2f2f2;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .container {
            display: flex;
            align-items: center;
            text-align: center;
        }

        #joystick-container {
            width: 200px;
            height: 200px;
            background-color: #e0e0e0;
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            position: relative;
        }

        #joystick {
            width: 80px;
            height: 80px;
            background-color: #3498db;
            border-radius: 50%;
            position: absolute;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <div class="container">
        <div id="joystick-container">
            <div id="joystick"></div>
        </div>

        <form action="" method="get" class="form-example"></form>
        <div id="button-container">
            <div id="joystick-value">Joystick Value: X: 0.00, Y: 0.00</div>
        </div>

    </div>

<script>
    const joystick = document.getElementById('joystick');

    let joystickX = 0;
    let joystickY = 0;

    let send = ["0", "0"];

    // Function to update the displayed joystick value
    function updateJoystickValue() {
        document.getElementById('joystick-value').textContent = `Joystick X: ${joystickX.toFixed(2)}, Y: ${-joystickY.toFixed(2)}`;
        
        var xhr = new XMLHttpRequest();
        send[0] = String(joystickX.toFixed(0));
        send[1] = String(joystickY.toFixed(0));
        xhr.open("GET", "/send?value="+send, true);
        xhr.send();
    }

    // Add event listeners to control the joystick
    joystick.addEventListener('mousedown', (e) => {
        document.addEventListener('mousemove', moveJoystick);
        document.addEventListener('mouseup', releaseJoystick);
    });

    function moveJoystick(e) {
        const container = document.getElementById('joystick-container');
        const rect = container.getBoundingClientRect();
        const centerX = rect.width / 2;
        const centerY = rect.height / 2;
        const x = e.clientX - rect.left - centerX;
        const y = e.clientY - rect.top - centerY;

        const distance = Math.min(Math.sqrt(x * x + y * y), centerX);
        const angle = Math.atan2(y, x);

        joystickX = distance * Math.cos(angle);
        joystickY = distance * Math.sin(angle);
        
        

        joystick.style.transform = `translate(${joystickX}px, ${joystickY}px)`;
        updateJoystickValue();
        handleButtonRelease(); // Immediately update button status
    }

    function releaseJoystick() {
        document.removeEventListener('mousemove', moveJoystick);
        joystick.style.transform = 'translate(0, 0)';
        joystickX = 0;
        joystickY = 0;
        updateJoystickValue();
        handleButtonRelease(); // Immediately update button status

        
    }

    document.addEventListener('keydown', (e) => {
        e.preventDefault(); // Prevent default keyboard event
        switch (e.key) {
            case 'w':
                // Move the joystick up
                joystickX = 0;
                joystickY = -100;
                break;
            case 's':
                // Move the joystick down
                joystickX = 0;
                joystickY = 100;
                break;
            case 'a':
                // Move the joystick left
                joystickX = -100;
                joystickY = 0;
                break;
            case 'd':
                // Move the joystick right
                joystickX = 100;
                joystickY = 0;
                break;
        }
        joystick.style.transform = `translate(${joystickX}px, ${joystickY}px)`;
        updateJoystickValue();
        handleButtonRelease(); // Immediately update button status

        
    })

    document.addEventListener('keyup', (e) => {
        joystickX = 0;
        joystickY = 0;
        joystick.style.transform = 'translate(0, 0)';
        updateJoystickValue();
        handleButtonRelease(); // Immediately update button status
    });

    // function sendDataToPython() {
    //     const data = {
    //         joystickX: joystickX,
    //         joystickY: joystickY,
    //     };

    //     fetch('/update_data', {
    //         method: 'POST',
    //         headers: {
    //             'Content-Type': 'application/json'
    //         },
    //         body: JSON.stringify(data)
    //     })
    //     .then(response => response.json())
    //     .then(data => {
    //         console.log(data.message);
    //     })
    //     .catch(error => {
    //         console.error('Error:', error);
    //     });
    // }

    // setInterval(sendDataToPython, 1000); // 1000 milliseconds (1 second)
</script>

</body>
</html>
'''

# Method for parsing and sending mqtt messages
def send_mqtt_message(x, y):
    message = f"{x},{y}"
    client.publish("Remote", message)

# Server class, implementation of GET method
class Server(BaseHTTPRequestHandler):    

    # def infinite_loop():
    #     print('Some magic')
    #     threading.Timer(60, infinite_loop()).start()

    def do_HEAD(self):
        return

    def do_GET(self):

        split_path = os.path.splitext(self.path)
        request_extension = split_path[1]

        # send header
        self.send_response(200) #response time
        self.send_header("Content-type", "text/html") 
        self.end_headers()

        # convert data to right format and send
        self.wfile.write(bytes(page, "utf-8"))
        if '/send' in self.path:
            x = self.path.split('=')[1].split(',')[0]
            y = self.path.split('=')[1].split(',')[1]
            print("Send: " + x + ',' + y)
            send_mqtt_message(x, y)

if __name__ == '__main__':
    httpd = HTTPServer((HOST_NAME, PORT_NUMBER), Server)
    print(time.asctime(), 'Server UP - %s:%s' % (HOST_NAME, PORT_NUMBER))
    
    try:
        # keep the server alive 
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    
    httpd.server_close()
    print(time.asctime(), 'Server DOWN - %s:%s' % (HOST_NAME, PORT_NUMBER))


