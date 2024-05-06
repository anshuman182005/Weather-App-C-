#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
	cout << "\t+-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-+" << endl;
	cout << "\t              Weather App              " << endl;
	cout << "\t+-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-+" << endl;
	string city;
	cout << "Enter The City Name : ";
	getline(cin, city);
	http_client client(U("https://api.openweathermap.org/data/2.5"));
	uri_builder builder(U("/weather"));
	builder.append_query(U("q"), utility::conversions::to_string_t(city));
	builder.append_query(U("appid"), U("43a33114fff1e70c8c5410b2315e34f9"));
	http_request request(methods::GET);
	request.set_request_uri(builder.to_string());
	client.request(request).then([](http_response response) {
		return response.extract_json();
	}).then([](web::json::value body) {
		double kelvin = body[U("main")][U("temp")].as_double();
		cout << "\tTemperature : " << (kelvin - 273.15) << " Celsius" << endl;
		cout << "\tHumidity : " << body[U("main")][U("humidity")].as_double() << " %" << endl;
		cout << "\tWeather : " << utility::conversions::to_utf8string(body[U("weather")][0][U("main")].as_string());
	}).wait();
	return 0;
}