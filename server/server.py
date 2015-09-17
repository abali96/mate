from weather_api_constants import weather_cmd_map
from bottle import request, route, run
from spark import SparkCoreConstants
from user_constants import UserConstants
import forecastio
import datetime
import re
import os


@route('/weather')
def weather():
    try:
        forecast = forecastio.load_forecast(os.environ["forecastio_key"], request.query.lat, request.query.lng)
    except:  # For now, catch all errors; we should just catch Bottle HTTPErrors
        forecast = forecastio.load_forecast(os.environ["forecastio_key"], UserConstants.DefaultLat, UserConstants.DefaultLng)
    current_weather = forecast.currently().__dict__["d"]["summary"]
    return SparkCoreConstants.WeatherStart + generate_return_str(current_weather) + SparkCoreConstants.Delimiter


def generate_return_str(current_weather):
    for weather_search_patterns, return_val in weather_cmd_map.items():
        if any(re.search(pattern, current_weather, re.IGNORECASE) for pattern in weather_search_patterns):
            return return_val
    print(current_weather)


@route('/time')
def time():
    hour_offset = int(request.query.hour_offset)if request.query.hour_offset != '' else 0
    minute_offset = int(request.query.minute_offset) if request.query.minute_offset != '' else 0
    current_time = datetime.datetime.utcnow() + datetime.timedelta(hours=hour_offset, minutes=minute_offset)
    return SparkCoreConstants.TimeStart + str(current_time.hour) + str(current_time.minute) + SparkCoreConstants.Delimiter


def run_server():
    run(host='0.0.0.0', port=8080)


if __name__ == '__main__':
    run_server()

app = bottle.default_app()
