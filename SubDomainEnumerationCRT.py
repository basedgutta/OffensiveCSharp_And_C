import requests
from bs4 import BeautifulSoup

def crtEnum(domain):
    subdomains = list()
    url = f"https://crt.sh/?q=%.{domain}&output=json"
    response = requests.get(url)
    data = response.json()

    # Parse the response for subdomains
    for item in data:
        subdomain = item['name_value']
        if subdomain.endswith(domain):
            subdomains.append(subdomain)

    return subdomains


#domain = "example.com"
#subdomainscrt = crtEnum(domain)
#print(subdomains)


