import logging
import os
import ssl

from flask import Flask
from flask_ask import Ask, request, session, question, statement

import paho.mqtt.publish as publish
import paho.mqtt.client as mqtt

# Enter your CloudMQTT endpoint and credentials
MQTT_HOST            = 'FQDN'
MQTT_WEBSOCKET_PORT  =  portnum
MQTT_USERNAME        =  'username'
MQTT_PASSWORD        =  'password'

# Non-flask functions

def control_led(action):
    '''Based on action, turn on or off led'''

    if action == 'on':
        logging.info('turning ON led')
        publish.single(
            topic='command',
            payload='led=on',
            client_id='alexa_skill',
            hostname=MQTT_HOST,
            port=MQTT_WEBSOCKET_PORT,
            auth = {
                'username': MQTT_USERNAME,
                'password': MQTT_PASSWORD
            },
            tls = {
                'ca_certs': './cloudmqtt.pem',
                'cert_reqs': ssl.CERT_NONE
            },
            transport='websockets',
            protocol=mqtt.MQTTv311
        )
    elif action == 'off':
        logging.info('turning OFF led')
        publish.single(
            topic='command',
            payload='led=off',
            client_id='alexa_skill',
            hostname=MQTT_HOST,
            port=MQTT_WEBSOCKET_PORT,
            auth = {
                'username': MQTT_USERNAME,
                'password': MQTT_PASSWORD
            },
            tls = {
                'ca_certs': './cloudmqtt.pem',
                'cert_reqs': ssl.CERT_NONE
            },
            transport='websockets',
            protocol=mqtt.MQTTv311
        )


app = Flask(__name__)
ask = Ask(app, "/")
logging.getLogger('flask_ask').setLevel(logging.DEBUG)


@ask.launch
def launch():
    speech_text = 'Welcome to Smart Device, you can say turn on, or turn off LED'
    return question(speech_text).reprompt(speech_text)


@ask.intent('led_on')
def led_on():
    control_led('on')
    speech_text = 'Turning on LED'
    return statement(speech_text)


@ask.intent('led_off')
def led_on():
    control_led('off')
    speech_text = 'Turning off LED'
    return statement(speech_text)


@ask.intent('AMAZON.HelpIntent')
def help():
    speech_text = 'You can say you can say turn on, or turn off LED'
    return question(speech_text).reprompt(speech_text)


@ask.session_ended
def session_ended():
    return "{}", 200


if __name__ == '__main__':
    if 'ASK_VERIFY_REQUESTS' in os.environ:
        verify = str(os.environ.get('ASK_VERIFY_REQUESTS', '')).lower()
        if verify == 'false':
            app.config['ASK_VERIFY_REQUESTS'] = False
    app.run(debug=True)