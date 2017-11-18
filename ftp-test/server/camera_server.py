import os
import json

from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import FTPHandler
from pyftpdlib.servers import FTPServer

class CameraServer:

    __server = None

    def __init__(self, login_credentials_path):

        # Move into correct directory for file path references
        os.chdir(os.path.dirname(__file__))

        # Open and parse login info
        with open(login_credentials_path) as config:
            login = json.load(config)

        # Define a new user having read-only permissions
        __authorizer = DummyAuthorizer()

        # photos_path = os.path.join(basepath, '/photos')
        __authorizer.add_user(login['username'],
            login['password'], './photos/', perm='elrad')

        # Instantiate FTP handler class
        __handler = FTPHandler
        __handler.authorizer = __authorizer

        # Instantiate FTP server class and listen on 127.0.0.1:2121
        address = ('', 2121)
        self.__server = FTPServer(address, __handler)

        # set a limit for connections
        self.__server.max_cons = 256
        self.__server.max_cons_per_ip = 5

    def start(self):
        self.__server.serve_forever()

    def close(self):
        self.__server.close()
