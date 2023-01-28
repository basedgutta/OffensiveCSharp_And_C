$ipRange = "192.168.1.1-192.168.1.255"
$liveHosts = Test-Connection -Count 1 -Quiet -ErrorAction SilentlyContinue (1..255 | % {"192.168.1.$_"})
$liveHosts | Select-Object Address

$hostname = "IP"
$wmi = [WMIClass]"\\$hostname\root\cimv2:Win32_OperatingSystem"
$wmi.Ping()
