from drone_client import DroneClient

def main():
    
    ftp_client = DroneClient('../login_credentials.config')
    ftp_client.downloadAllPhotos()
    ftp_client.quit()

if __name__ == '__main__':
    main()
