import os

Import("env")

try:
    from dotenv import load_dotenv
    load_dotenv()
except:
    env.Execute("$PYTHONEXE -m pip install -r requirements.txt")
    from dotenv import load_dotenv
    load_dotenv()

env.Append(CPPDEFINES=[
    ("HOTSPOT_PW", env.StringifyMacro(os.getenv("CNCD_HOTSPOT_PW")))
])
