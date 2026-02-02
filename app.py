import http.server
import socketserver
import webbrowser
import threading
import time
import subprocess
import os

PORT = 8080
logged_in = False


class LoginHandler(http.server.BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        with open("web/login.html", "rb") as f:
            self.wfile.write(f.read())

    def do_POST(self):
        global logged_in

        length = int(self.headers.get("Content-Length", 0))
        data = self.rfile.read(length).decode()

        if "username=admin" in data and "password=1234" in data:
            logged_in = True
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()

            # Dragon splash + center + bigger + hack font
            self.wfile.write(b"""
            <html>
            <body style="background:black; color:#00ff00; text-align:center; font-family:monospace;">

            <div style="display:flex; justify-content:center; align-items:center; margin-top:60px;">
                <img src='https://i.ibb.co/TD4K1ypS/dragon.png' style="width:600px;">
            </div>

            <div style="margin-top:30px;">
                <h2 style="font-size:28px; font-weight:bold;">Login Successful</h2>
                <p style="font-size:20px;">Initializing Mini OS....</p>
            </div>

            </body>
            </html>
            """)

        else:
            self.send_response(401)
            self.end_headers()
            self.wfile.write(b"Invalid credentials")


def open_browser():
    time.sleep(1)
    webbrowser.open(f"http://localhost:{PORT}")


if __name__ == "__main__":
    threading.Thread(target=open_browser).start()

    with socketserver.TCPServer(("", PORT), LoginHandler) as httpd:
        while not logged_in:
            httpd.handle_request()

    os.system("cls")
    
    # Separate CMD launch like original
    subprocess.Popen(["cmd", "/c", "start", "cmd", "/k", "minios.exe"])
