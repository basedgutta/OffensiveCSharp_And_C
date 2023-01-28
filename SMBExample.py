from impacket import smb

ip = ""
username = ""
password = ""
remote_system = smb.SMB(ip, username, password)
remote_system.login()
shares = remote_system.listShares()
for share in shares:
    print(share["shi1_netname"].decode("utf-8"))
