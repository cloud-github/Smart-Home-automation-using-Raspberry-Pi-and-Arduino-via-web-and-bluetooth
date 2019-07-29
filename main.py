import serial
from flask import Flask, render_template, request

app = Flask(__name__)
@app.route("/")
def index():
    templateData = {
      'lights_status'  : "OFF",
      'fan_status'  : "OFF",
      'tv_status'  : "OFF",
      'all_devices'  : "OFF",
      }
    return render_template('index.html', **templateData)
    
# The function below is executed when someone requests a URL with the actuator name and action in it:
@app.route("/<deviceName>/<action>")
def action(deviceName, action):    
    try:
        lights_status = "";
        fan_status = "";
        tv_status = "";
        all_devices = "";
        port = serial.Serial("/dev/rfcomm0", baudrate=9600, timeout=2)      #reading and writing data from and to arduino serially.
        if deviceName == 'lights' and action == 'on':
            print("lights on")
            port.write("lights_on".encode())
            lights_status = port.readline()
            if(port.readline() == 1):
                lights_status = "OFF"
            else:
                lights_status = "ON"    
        
        if deviceName == 'lights' and action == 'off':
            print("lights off")
            port.write("lights_off".encode())
            if(port.readline() == 0):
                lights_status = "ON"
            else:
                lights_status = "OFF"
            
        if deviceName == 'fan' and action == 'on':
            print("fan on")
            port.write("fan_on".encode())
            if(port.readline() == 1):
                fan_status = "OFF"
            else:
                fan_status = "ON"
            
        if deviceName == 'fan' and action == 'off':
            print("fan off")
            port.write("fan_off".encode())
            if(port.readline() == 0):
                fan_status = "ON"
            else:
                fan_status = "OFF"
            
        if deviceName == 'tv' and action == 'on':
            print("tv on")
            port.write("tv_on".encode())
            if(port.readline() == 1):
                tv_status = "OFF"
            else:
                tv_status = "ON"
            
        if deviceName == 'tv' and action == 'off':
            print("tv off")
            port.write("tv_off".encode())
            if(port.readline() == 0):
                tv_status = "ON"
            else:
                tv_status = "OFF"
                
        if deviceName == 'turn_all' and action == 'off':
            print("turn all off")
            port.write("turn_all_off".encode())
            if(port.readline() == 0):
                all_devices = "ON"
            else:
                all_devices = "OFF" 
         
        if deviceName == 'turn_all' and action == 'on':
            print("turn all on")
            port.write("turn_all_on".encode())
            if(port.readline() == 1):
                all_devices = "OFF"
            else:
                all_devices = "ON"          

        templateData = {
          'lights_status'  : lights_status,
          'fan_status'  : fan_status,
          'tv_status'  : tv_status,
          'all_devices'  : all_devices,
        }
        return render_template('index.html', **templateData)
    except:
        templateData = {
          'error_connection'  : "Error communicating low-power radio waves"
        }
        return render_template('error.html', **templateData)

if __name__ == "__main__":
   app.run(host='0.0.0.0', port=80, debug=True)
