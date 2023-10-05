import random

# Log entry format:
# Hostname | Timestamp | Request | HTTP Response Code | Bytes
log_entry_format = "{hostname}-[{timestamp}] \"GET {resource} HTTP/1.0\" 200 {bytes}\n"

# Hostnames
hostnames = ["unicomp6.unicomp.net", "burger.letters.com", "d104.aa.net"]

# Resources
resources = ["/shuttle/countdown/", "/shuttle/countdown/liftoff.html", "/images/NASA-logosmall.gif"]

# Timestamps
timestamps = ["01/Jul/1995:00:00:06 -0400", "01/Jul/1995:00:00:11 -0400", "01/Jul/1995:00:00:12 -0400"]

# Bytes (randomly generated within a reasonable range)
bytes_values = [random.randint(0, 10000) for _ in range(10)]

# Generating log entries
with open("hosts_access_log_00.txt", "w") as log_file:
    for i in range(20):  # Generating 20 log entries
        hostname = random.choice(hostnames)
        timestamp = random.choice(timestamps)
        resource = random.choice(resources)
        bytes_value = random.choice(bytes_values)
        log_entry = log_entry_format.format(hostname=hostname, timestamp=timestamp, resource=resource, bytes=bytes_value)
        log_file.write(log_entry)

print("Sample log file generated: hosts_access_log_00.txt")
