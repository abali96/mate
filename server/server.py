from weather_api_constants import weather_cmd_map
from bottle import request, route, run
from spark import SparkCoreConstants
from user_constants import UserConstants
from yahoo_finance import Share
import forecastio
import datetime
import re
import os

os.environ["forecastio_key"] = "371f773375860e914bd1731fe69a5da8"


@route('/weather')
def weather():
    try:
        forecast = forecastio.load_forecast(os.environ["forecastio_key"], request.query.lat, request.query.lng)
    except:  # For now, catch all errors; we should just catch Bottle HTTPErrors
        forecast = forecastio.load_forecast(os.environ["forecastio_key"], UserConstants.DefaultLat, UserConstants.DefaultLng)
    current_weather = forecast.currently().__dict__["d"]["summary"]
    return SparkCoreConstants.WeatherStart + str(generate_return_str(current_weather)) + SparkCoreConstants.Delimiter


def generate_return_str(current_weather):
    for weather_search_patterns, return_val in weather_cmd_map.items():
        if any(re.search(pattern, current_weather, re.IGNORECASE) for pattern in weather_search_patterns):
            return return_val


@route('/time')
def time():
    hour_offset = int(request.query.hour_offset) if request.query.hour_offset != '' else 0
    minute_offset = int(request.query.minute_offset) if request.query.minute_offset != '' else 0
    current_time = datetime.datetime.utcnow() + datetime.timedelta(hours=hour_offset, minutes=minute_offset)
    return SparkCoreConstants.TimeStart + "%02d" % current_time.hour + "%02d" % current_time.minute + SparkCoreConstants.Delimiter


@route('/stocks')
def stock():
    return_str = SparkCoreConstants.StockStart
    for key, share_name in request.query.items():
        return_str += share_name + "  " + str(Share(share_name).get_price()) + "  "

    return_str += SparkCoreConstants.Delimiter
    return return_str


def run_server():
    run(host='0.0.0.0', port=int(os.environ.get('PORT', 5000)))


if __name__ == '__main__':
    run_server()

app = bottle.default_app()
