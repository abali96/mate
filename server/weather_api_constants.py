class WeatherTypes:
    ''' This class is used to collect all of the weather condition variations that are similar for our purposes. '''
    Clear = [r'clear']
    Rain = [r'rain']
    Cloudy = [r'cloudy', r'fog']
    Snow = [r'snow', r'sleet', r'hail']
    Thunderstorm = [r'thunderstorm']


class WeatherReturnValues:
    ''' This class maps weather conditions to constant terms
        interpreted by the spark core. '''
    Clear = "sunny"
    Rain = "rain"
    Cloudy = "clouds"
    Snow = "snow"
    Thunderstorm = "lightning"


class WeatherConstants:
    ''' Hard code the latitude and longitude of weather we're serving for now '''
    Lat = 43.4722850
    Lng = -80.5448580

weather_cmd_map = {
    tuple(WeatherTypes.Clear): WeatherReturnValues.Clear,
    tuple(WeatherTypes.Rain): WeatherReturnValues.Rain,
    tuple(WeatherTypes.Cloudy): WeatherReturnValues.Cloudy,
    tuple(WeatherTypes.Snow): WeatherReturnValues.Snow,
    tuple(WeatherTypes.Thunderstorm): WeatherReturnValues.Thunderstorm,
}
