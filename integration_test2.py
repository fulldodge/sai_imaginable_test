import redis
import time
import subprocess

# connecting to redis
r = redis.Redis(host='localhost', port=6379, db=4)  # db=4 — APPL_DB в SONiC

# writing port config
r.hset("PORT_TABLE:Ethernet0", "admin_status", "up")
r.hset("PORT_TABLE:Ethernet0", "mtu", "9100")

print("[TEST] Writed to REDIS: PORT_TABLE:Ethernet0 admin_status=up")

# Wait for SyncD start work
time.sleep(1)

# Log check/wait for SAI call
result = subprocess.run(
    ["grep", "sai_set_port_attribute", "/var/log/syslog"],
    capture_output=True,
    text=True
)

if "sai_set_port_attribute" in result.stdout:
    print("[TEST] SUCCEED: SAI log was found")
    exit(0)
else:
    print("[TEST] ERROR: SAI log was NOT found  ")
    exit(1)