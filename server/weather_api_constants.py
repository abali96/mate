class WeatherTypes:
    ''' This class is used to collect all of the weather condition variations that are similar for our purposes. '''
    Clear = [r'clear']
    Rain = [r'rain', r'drizzle']
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

weather_cmd_map = {
    tuple(WeatherTypes.Clear): WeatherReturnValues.Clear,
    tuple(WeatherTypes.Rain): WeatherReturnValues.Rain,
    tuple(WeatherTypes.Cloudy): WeatherReturnValues.Cloudy,
    tuple(WeatherTypes.Snow): WeatherReturnValues.Snow,
    tuple(WeatherTypes.Thunderstorm): WeatherReturnValues.Thunderstorm,
}
