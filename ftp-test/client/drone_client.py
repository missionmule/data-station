import json
import os

from ftplib import FTP

class DroneClient:

    __client = None    # Pseudo-private variable

    def __init__(self, login_credentials_path):

        # Move into correct directory for file path references
        os.chdir(os.path.dirname(__file__))

        # Get server login credentials
        with open(login_credentials_path) as config:
            login = json.load(config)

        self.__client = FTP('')
        self.__client.connect('localhost',2121)
        self.__client.login(login['username'], login['password'])
        self.__client.cwd('.')

    def list_files(self):
        return self.__client.nlst()

    def downloadFile(self, file_name):
        # Create new file in downloads directory with same file name
        local_file = open('./downloads/'+file_name, 'wb')

        # Download the file in 1024 byte chunks so buffer does not overflow
        self.__client.retrbinary('RETR ' + file_name, local_file.write, 1024)

        local_file.close()

    def downloadAllPhotos(self):
        for file_name in self.list_files():
            self.downloadFile(file_name)

    def quit(self):
        self.__client.quit()
