import dns.resolver

def enumerate_subdomains(domain):
    subdomains = set()
    try:
        answers = dns.resolver.query(domain, 'NS')
        for rdata in answers:
            subdomains.add(str(rdata))
    except:
        pass
    try:
        answers = dns.resolver.query(domain, 'MX')
        for rdata in answers:
            subdomains.add(str(rdata.exchange))
    except:
        pass
    try:
        answers = dns.resolver.query(domain, 'A')
        for rdata in answers:
            subdomains.add(str(rdata))
    except:
        pass
    try:
        answers = dns.resolver.query(domain, 'AAAA')
        for rdata in answers:
            subdomains.add(str(rdata))
    except:
        pass
    try:
        answers = dns.resolver.query(domain, 'CNAME')
        for rdata in answers:
            subdomains.add(str(rdata.target))
    except:
        pass
    return subdomains

domain = "example.com"
subdomains = enumerate_subdomains(domain)
for subdomain in subdomains:
    print(" " + subdomain)
