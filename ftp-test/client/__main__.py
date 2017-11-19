from drone_client import DroneClient

def main():

    # ftp_client = DroneClient('../login_credentials.config', '192.168.10.154')
    ftp_client = DroneClient('../login_credentials.config', 'localhost')
    ftp_client.downloadAllPhotos()
    ftp_client.quit()

if __name__ == '__main__':
    main()
