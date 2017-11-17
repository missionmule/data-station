from camera_server import CameraServer

def main():

    ftp_server = CameraServer('../login_credentials.config')
    ftp_server.start()

if __name__ == '__main__':
    main()
