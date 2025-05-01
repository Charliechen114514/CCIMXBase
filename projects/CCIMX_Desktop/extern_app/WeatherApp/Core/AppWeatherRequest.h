#ifndef APPWEATHERREQUEST_H
#define APPWEATHERREQUEST_H
#include "MyWeatherRequest.h"

class AppWeatherResult : public WeatherResult {
public:
	explicit AppWeatherResult(QObject* parent = nullptr)
		: WeatherResult(parent) { }
	void parseJsonString(const QString json) override;
	void debugPrint() const;

	struct DailyWeather {
		QString date;
		QString textDay;
		QString textNight;
		QString high;
		QString low;
		QString windDirection;
		QString windScale;
		QString humidity;
	};
	QString cached_city;
	QList<DailyWeather> daily_weather;
};

class AppWeatherRequest : public WeatherRequest {
public:
	Q_DISABLE_COPY(AppWeatherRequest);
	AppWeatherRequest(QObject* parent = nullptr)
		: WeatherRequest(parent) { };
	/* add our query issue here */
	QUrlQuery compose_request() override;
};

#endif // APPWEATHERREQUEST_H
