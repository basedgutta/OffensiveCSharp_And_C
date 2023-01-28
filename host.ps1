$ipRange = "192.168.1.1-192.168.1.255"
$liveHosts = Test-Connection -Count 1 -Quiet -ErrorAction SilentlyContinue (1..255 | % {"192.168.1.$_"})
$liveHosts | Select-Object Address

$hostname = "IP"
$wmi = [WMIClass]"\\$hostname\root\cimv2:Win32_OperatingSystem"
$wmi.Ping()


#$ipRange = "192.168.1.1-254"

#$ips = $ipRange.Split("-")
#$startIP = [System.Net.IPAddress]::Parse($ips[0])
#$endIP = [System.Net.IPAddress]::Parse($ips[1])
#$ipAddresses = [System.Net.IPAddress]::GetAddressBytes($startIP)..[System.Net.IPAddress]::GetAddressBytes($endIP) | % {
 #   [System.Net.IPAddress]::New($_[0], $_[1], $_[2], $_[3])
#}

#$liveHosts = @()
#$ipAddresses | % {
 #   $host = $_.ToString()
   # if (Test-Connection -ComputerName $host -Count 1 -Quiet) {
    #    $liveHosts += $host
   # }
#}

# $liveHosts
