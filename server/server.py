from weather_api_constants import weather_cmd_map, WeatherConstants
from bottle import route, run, template
from spark import SparkCoreConstants
import forecastio
import datetime
import api_keys
import re


@route('/weather')
def weather():
    forecast = forecastio.load_forecast(api_keys.ForecastIOApiKey, WeatherConstants.Lat, WeatherConstants.Lng)
    current_weather = forecast.currently().__dict__["d"]["summary"]
    return SparkCoreConstants.WeatherStart + generate_return_str(current_weather) + SparkCoreConstants.Delimiter


def generate_return_str(current_weather):
    for weather_search_patterns, return_val in weather_cmd_map.items():
        if any(re.search(pattern, current_weather, re.IGNORECASE) for pattern in weather_search_patterns):
            return return_val


@route('/time')
def time():
    current_time = datetime.datetime.now().time()
    return SparkCoreConstants.TimeStart + str(current_time.hour) + str(current_time.minute) + SparkCoreConstants.Delimiter

print(weather())
print(time())
