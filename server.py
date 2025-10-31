from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit
from datetime import datetime

app = Flask(__name__)
socketio = SocketIO(app)  # Initialize SocketIO for WebSockets

message_count = 0  # Counter for message serial numbers

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/alert", methods=["POST"])
def alert():
    global message_count
    data = request.get_json()
    message = data.get("message", "No message")
    
    # Generate timestamp and increment message count
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    message_count += 1
    full_message = f"#{message_count} | {timestamp} | {message}"

    # Emit the message to the frontend via WebSocket
    socketio.emit("new_alert", {"serial": message_count, "timestamp": timestamp, "message": message})

    # Save message to a log file
    with open("log.txt", "a") as log_file:
        log_file.write(full_message + "\n")

    print("Received alert:", full_message)  # Print for server log
    return "Alert received", 200

if __name__ == "__main__":
    socketio.run(app, host="0.0.0.0", port=5000)