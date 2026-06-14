import os
import resend

resend.api_key = os.environ["RESEND_API_KEY"]

results_file = open("results.txt", "r")

for line in results_file:
    elements = line.split(",")
    cur_name = elements[0]
    cur_email = elements[1]
    assigned_name = elements[2]

    

    params: resend.Emails.SendParams = {
        "from": "CGSanta <info@cgsanta.com>",
        "to": [cur_email],
        "subject": "Secret Santa Assignment",
        "html": f"<strong>Hi {cur_name}!\nYou were assigned {assigned_name}</strong>",
    }

    email = resend.Emails.send(params)
    print(email)

results_file.close()
