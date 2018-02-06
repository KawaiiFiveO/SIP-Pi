#!/usr/bin/env python

import sys
import smtplib
from os.path import basename
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.utils import COMMASPACE, formatdate


# config
server = "send.example.com"
port = 587
send_from = "raspi@example.de"
password = "verynicepassword"
send_to = "some@email.example"
subject = "Message from your answering machine"


def send_mail(text, f):

    msg = MIMEMultipart()
    msg['From'] = send_from
    msg['To'] = send_to
    msg['Date'] = formatdate(localtime=True)
    msg['Subject'] = subject

    msg.attach(MIMEText(text))

    try:
        with open(f, "rb") as fil:
            part = MIMEApplication(
                fil.read(),
                Name=basename(f)
            )
            part['Content-Disposition'] = 'attachment; filename="%s"' % basename(f)
            msg.attach(part)
    except IOError as e:
        print "Can not read file \""+f+"\": I/O error({0}): {1}".format(e.errno, e.strerror)
    except:
        print "Can not read file", sys.exc_info()[0]
        raise

    s = smtplib.SMTP(server, port)
    # s.debuglevel = 1
    s.ehlo()
    s.starttls()
    # s.ehlo
    s.login(send_from, password)
    s.sendmail(send_from, send_to, msg.as_string())
    s.quit()

    # smtp.close()

if len(sys.argv) == 3:
    send_mail(sys.argv[1],sys.argv[2])
else:
    print"provide two arguments: \"text\" \"file\""
