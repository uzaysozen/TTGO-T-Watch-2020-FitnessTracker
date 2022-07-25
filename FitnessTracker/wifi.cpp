#include "config.h"

const char *ssid = "REPLACE_WITH_YOUR_SSID";
const char *password = "REPLACE_WITH_YOUR_PASSWORD";

const char *ntpServer = "pool.ntp.org";
const char *cloudServer = "https://ttgo-watch-default-rtdb.europe-west1.firebasedatabase.app/exercise.json";
const long gmtOffset_sec = 0; // GMT 0
const int daylightOffset_sec = 3600; //Daylight time +1

const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFkjCCBHqgAwIBAgIRAPNL60SqeQv6EGsLkFIgHQkwDQYJKoZIhvcNAQELBQAw\n" \
"RjELMAkGA1UEBhMCVVMxIjAgBgNVBAoTGUdvb2dsZSBUcnVzdCBTZXJ2aWNlcyBM\n" \
"TEMxEzARBgNVBAMTCkdUUyBDQSAxRDQwHhcNMjIwNTA0MTQwNzAyWhcNMjIwODAy\n" \
"MTQwNzAxWjAuMSwwKgYDVQQDDCMqLmV1cm9wZS13ZXN0MS5maXJlYmFzZWRhdGFi\n" \
"YXNlLmFwcDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKHCTMGyWm/l\n" \
"tewZ4taLdJCvmW62UgFOKWQUNQ2NUztq/uNJ9xdGYU+kXPUHapTD0Uxks0ql7KUW\n" \
"JsXhTSfUjoOn68nQ/oNhVU7zaGE885dBYgNuO8pHK6HpXOo6eHW/DzQoR+luUQMm\n" \
"diD41LjFxtb6tvgC6dcWjKKaleXZ/iJ/UZSPFJG1i/lkY4JV8EZp0dbBpj95Eo4y\n" \
"uJTf85a5DyAjX8QF+z5+Bn/KPfN9eT70bvSOop9AiDdik3vs/6lKBtbD6EpqrHHq\n" \
"GXbzVsGyRe7ZLku6MqN0MnrqYddkQQMe7nkiw4slymjdGyAyshgKelWX3u3g5Hjs\n" \
"wwfdHhNsWTcCAwEAAaOCApEwggKNMA4GA1UdDwEB/wQEAwIFoDATBgNVHSUEDDAK\n" \
"BggrBgEFBQcDATAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBSpwbbyQttgx5i5JTUy\n" \
"5cqh36noJTAfBgNVHSMEGDAWgBQl4hgOsleRlCrl1F2GkIPeU7O4kjB7BggrBgEF\n" \
"BQcBAQRvMG0wOAYIKwYBBQUHMAGGLGh0dHA6Ly9vY3NwLnBraS5nb29nL3MvZ3Rz\n" \
"MWQ0aW50LzFHWVhPdDh1WjY0MDEGCCsGAQUFBzAChiVodHRwOi8vcGtpLmdvb2cv\n" \
"cmVwby9jZXJ0cy9ndHMxZDQuZGVyMC4GA1UdEQQnMCWCIyouZXVyb3BlLXdlc3Qx\n" \
"LmZpcmViYXNlZGF0YWJhc2UuYXBwMCEGA1UdIAQaMBgwCAYGZ4EMAQIBMAwGCisG\n" \
"AQQB1nkCBQMwPwYDVR0fBDgwNjA0oDKgMIYuaHR0cDovL2NybHMucGtpLmdvb2cv\n" \
"Z3RzMWQ0aW50LzhtdWJSejUyY2RVLmNybDCCAQUGCisGAQQB1nkCBAIEgfYEgfMA\n" \
"8QB2AEHIyrHfIkZKEMahOglCh15OMYsbA+vrS8do8JBilgb2AAABgI+cQyQAAAQD\n" \
"AEcwRQIgXGLpJHHY4WcaR8H76I7ak9x4B3WJOP+GPdrdjeZG8IYCIQCvAanB3O9C\n" \
"vkGPKpyKNjdQf7xsvy0N7vmlQHUQhyvS3wB3ACl5vvCeOTkh8FZzn2Old+W+V32c\n" \
"YAr4+U1dJlwlXceEAAABgI+cQt0AAAQDAEgwRgIhAKAj7oMJbeIASTAJIqzVjFnl\n" \
"LYnsBzCns1VkTbaWQCgtAiEAjSXDy4OL2oRjb7h5xoMTbgVFgySXQE7Xbj9u9Ob3\n" \
"2s4wDQYJKoZIhvcNAQELBQADggEBAGbBpUQjvmtBvfksaZs7WeYJOYysdQZ7P2G1\n" \
"BE3u1ZI7VhM5PYaihpobMqOes2mE1zPB8+er/E4h2b5vJsOwy6zQjcCcOlIIT0i4\n" \
"cCF6P23B7hQNLK12TgFbhugt1ORmgAc4iHEfJ7er0qYM0GIYBTzm5UTmp2UmrXjh\n" \
"Ren8FJbVTdGNgswSQ6lkC4KRTbXkzDXvPRmNt2S6r5ZU95hqylGz2mpouvPcFJEE\n" \
"97T0HrAFnDSlkcCwC58XfWFilm3CeSdVPWNlXmbbAMWtScZsj8BTGi0L3vQNuxTl\n" \
"L7PKnzFIFWuznMbiGQOk/uaGsrXwwoI1KHfXWkyTib1b/n3U+5A=\n" \
"-----END CERTIFICATE-----\n" \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFjDCCA3SgAwIBAgINAgCOsgIzNmWLZM3bmzANBgkqhkiG9w0BAQsFADBHMQsw\n" \
"CQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEU\n" \
"MBIGA1UEAxMLR1RTIFJvb3QgUjEwHhcNMjAwODEzMDAwMDQyWhcNMjcwOTMwMDAw\n" \
"MDQyWjBGMQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZp\n" \
"Y2VzIExMQzETMBEGA1UEAxMKR1RTIENBIDFENDCCASIwDQYJKoZIhvcNAQEBBQAD\n" \
"ggEPADCCAQoCggEBAKvAqqPCE27l0w9zC8dTPIE89bA+xTmDaG7y7VfQ4c+mOWhl\n" \
"UebUQpK0yv2r678RJExK0HWDjeq+nLIHN1Em5j6rARZixmyRSjhIR0KOQPGBMUld\n" \
"saztIIJ7O0g/82qj/vGDl//3t4tTqxiRhLQnTLXJdeB+2DhkdU6IIgx6wN7E5NcU\n" \
"H3Rcsejcqj8p5Sj19vBm6i1FhqLGymhMFroWVUGO3xtIH91dsgy4eFKcfKVLWK3o\n" \
"2190Q0Lm/SiKmLbRJ5Au4y1euFJm2JM9eB84Fkqa3ivrXWUeVtye0CQdKvsY2Fka\n" \
"zvxtxvusLJzLWYHk55zcRAacDA2SeEtBbQfD1qsCAwEAAaOCAXYwggFyMA4GA1Ud\n" \
"DwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwEgYDVR0T\n" \
"AQH/BAgwBgEB/wIBADAdBgNVHQ4EFgQUJeIYDrJXkZQq5dRdhpCD3lOzuJIwHwYD\n" \
"VR0jBBgwFoAU5K8rJnEaK0gnhS9SZizv8IkTcT4waAYIKwYBBQUHAQEEXDBaMCYG\n" \
"CCsGAQUFBzABhhpodHRwOi8vb2NzcC5wa2kuZ29vZy9ndHNyMTAwBggrBgEFBQcw\n" \
"AoYkaHR0cDovL3BraS5nb29nL3JlcG8vY2VydHMvZ3RzcjEuZGVyMDQGA1UdHwQt\n" \
"MCswKaAnoCWGI2h0dHA6Ly9jcmwucGtpLmdvb2cvZ3RzcjEvZ3RzcjEuY3JsME0G\n" \
"A1UdIARGMEQwCAYGZ4EMAQIBMDgGCisGAQQB1nkCBQMwKjAoBggrBgEFBQcCARYc\n" \
"aHR0cHM6Ly9wa2kuZ29vZy9yZXBvc2l0b3J5LzANBgkqhkiG9w0BAQsFAAOCAgEA\n" \
"IVToy24jwXUr0rAPc924vuSVbKQuYw3nLflLfLh5AYWEeVl/Du18QAWUMdcJ6o/q\n" \
"FZbhXkBH0PNcw97thaf2BeoDYY9Ck/b+UGluhx06zd4EBf7H9P84nnrwpR+4GBDZ\n" \
"K+Xh3I0tqJy2rgOqNDflr5IMQ8ZTWA3yltakzSBKZ6XpF0PpqyCRvp/NCGv2KX2T\n" \
"uPCJvscp1/m2pVTtyBjYPRQ+QuCQGAJKjtN7R5DFrfTqMWvYgVlpCJBkwlu7+7KY\n" \
"3cTIfzE7cmALskMKNLuDz+RzCcsYTsVaU7Vp3xL60OYhqFkuAOOxDZ6pHOj9+OJm\n" \
"YgPmOT4X3+7L51fXJyRH9KfLRP6nT31D5nmsGAOgZ26/8T9hsBW1uo9ju5fZLZXV\n" \
"VS5H0HyIBMEKyGMIPhFWrlt/hFS28N1zaKI0ZBGD3gYgDLbiDT9fGXstpk+Fmc4o\n" \
"lVlWPzXe81vdoEnFbr5M272HdgJWo+WhT9BYM0Ji+wdVmnRffXgloEoluTNcWzc4\n" \
"1dFpgJu8fF3LG0gl2ibSYiCi9a6hvU0TppjJyIWXhkJTcMJlPrWx1VytEUGrX2l0\n" \
"JDwRjW/656r0KVB02xHRKvm2ZKI03TglLIpmVCK3kBKkKNpBNkFt8rhafcCKOb9J\n" \
"x/9tpNFlQTl7B39rJlJWkR17QnZqVptFePFORoZmFzM=\n" \
"-----END CERTIFICATE-----\n" \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFVzCCAz+gAwIBAgINAgPlk28xsBNJiGuiFzANBgkqhkiG9w0BAQwFADBHMQsw\n" \
"CQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEU\n" \
"MBIGA1UEAxMLR1RTIFJvb3QgUjEwHhcNMTYwNjIyMDAwMDAwWhcNMzYwNjIyMDAw\n" \
"MDAwWjBHMQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZp\n" \
"Y2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3QgUjEwggIiMA0GCSqGSIb3DQEBAQUA\n" \
"A4ICDwAwggIKAoICAQC2EQKLHuOhd5s73L+UPreVp0A8of2C+X0yBoJx9vaMf/vo\n" \
"27xqLpeXo4xL+Sv2sfnOhB2x+cWX3u+58qPpvBKJXqeqUqv4IyfLpLGcY9vXmX7w\n" \
"Cl7raKb0xlpHDU0QM+NOsROjyBhsS+z8CZDfnWQpJSMHobTSPS5g4M/SCYe7zUjw\n" \
"TcLCeoiKu7rPWRnWr4+wB7CeMfGCwcDfLqZtbBkOtdh+JhpFAz2weaSUKK0Pfybl\n" \
"qAj+lug8aJRT7oM6iCsVlgmy4HqMLnXWnOunVmSPlk9orj2XwoSPwLxAwAtcvfaH\n" \
"szVsrBhQf4TgTM2S0yDpM7xSma8ytSmzJSq0SPly4cpk9+aCEI3oncKKiPo4Zor8\n" \
"Y/kB+Xj9e1x3+naH+uzfsQ55lVe0vSbv1gHR6xYKu44LtcXFilWr06zqkUspzBmk\n" \
"MiVOKvFlRNACzqrOSbTqn3yDsEB750Orp2yjj32JgfpMpf/VjsPOS+C12LOORc92\n" \
"wO1AK/1TD7Cn1TsNsYqiA94xrcx36m97PtbfkSIS5r762DL8EGMUUXLeXdYWk70p\n" \
"aDPvOmbsB4om3xPXV2V4J95eSRQAogB/mqghtqmxlbCluQ0WEdrHbEg8QOB+DVrN\n" \
"VjzRlwW5y0vtOUucxD/SVRNuJLDWcfr0wbrM7Rv1/oFB2ACYPTrIrnqYNxgFlQID\n" \
"AQABo0IwQDAOBgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4E\n" \
"FgQU5K8rJnEaK0gnhS9SZizv8IkTcT4wDQYJKoZIhvcNAQEMBQADggIBAJ+qQibb\n" \
"C5u+/x6Wki4+omVKapi6Ist9wTrYggoGxval3sBOh2Z5ofmmWJyq+bXmYOfg6LEe\n" \
"QkEzCzc9zolwFcq1JKjPa7XSQCGYzyI0zzvFIoTgxQ6KfF2I5DUkzps+GlQebtuy\n" \
"h6f88/qBVRRiClmpIgUxPoLW7ttXNLwzldMXG+gnoot7TiYaelpkttGsN/H9oPM4\n" \
"7HLwEXWdyzRSjeZ2axfG34arJ45JK3VmgRAhpuo+9K4l/3wV3s6MJT/KYnAK9y8J\n" \
"ZgfIPxz88NtFMN9iiMG1D53Dn0reWVlHxYciNuaCp+0KueIHoI17eko8cdLiA6Ef\n" \
"MgfdG+RCzgwARWGAtQsgWSl4vflVy2PFPEz0tv/bal8xa5meLMFrUKTX5hgUvYU/\n" \
"Z6tGn6D/Qqc6f1zLXbBwHSs09dR2CQzreExZBfMzQsNhFRAbd03OIozUhfJFfbdT\n" \
"6u9AWpQKXCBfTkBdYiJ23//OYb2MI3jSNwLgjt7RETeJ9r/tSQdirpLsQBqvFAnZ\n" \
"0E6yove+7u7Y/9waLd64NnHi/Hm3lCXRSHNboTXns5lndcEZOitHTtNCjv0xyBZm\n" \
"2tIMPNuzjsmhDYAPexZ3FL//2wmUspO8IFgV6dtxQ/PeEMMA3KgqlbbC1j+Qa3bb\n" \
"bP6MvPJwNQzcmRk13NfIRmPVNnGuV/u3gm3c\n" \
"-----END CERTIFICATE-----\n";                                      

String exerciseData;
HTTPClient http;

void initTime(void);

void WiFiDisconnectedEventHandler(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Trying to Reconnect");
  WiFi.begin(ssid, password);
}

void WiFiConnectedEventHandler(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Connected to Wifi successfully!");
  delay(1000);
  initTime();
}

void setupNetwork(void) {
  WiFi.disconnect(true);

  delay(1000);

  WiFi.onEvent(WiFiConnectedEventHandler, SYSTEM_EVENT_STA_CONNECTED);
  WiFi.onEvent(WiFiDisconnectedEventHandler, SYSTEM_EVENT_STA_DISCONNECTED);

  WiFi.begin(ssid, password);
}

void initTime(void) {
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time, Restart in 3 seconds");
      tft->println("Failed to obtain time, Restart in 3 seconds");
      delay(3000);
      esp_restart();
      while (1);
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.println("Time synchronization succeeded");
  // Sync local time to external RTC
  rtc->syncToRtc();
}

String httpGETRequest(const char* serverName) {
  Serial.println(serverName);
 
  http.begin(serverName, root_ca);
  
  // Send HTTP GET request
  int httpResponse = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponse>0) {
    Serial.print("HTTP Response: ");
    Serial.println(httpResponse);
    payload = http.getString();
  }
  else {
    Serial.print("Error: ");
    Serial.println(httpResponse);
  }
  // Free resources
  http.end();
  return payload;
}

void httpPOSTRequest(const char* serverName) {
  Serial.println(serverName);
    
  http.begin(serverName, root_ca);

  http.addHeader("Content-Type", "application/json");
  String date = (String) dday +  "/" + (String) mmonth +  "/" + (String) yyear;
  String httpData = "{\"calories\":" + (String) (stepCount * caloriesMultiplier) + ",\"date\":\"" + date + "\",\"distance\":" + (String) (stepCount * stepLength) + ",\"stepcount\":" + stepCount + ",\"targetsteps\":" + userTargetSteps + ",\"username\":\"" + userName + "\"}";
  Serial.println(httpData);
  // Send HTTP POST request
  int httpResponse = http.POST(httpData);
  
  Serial.print("HTTP Response: ");
  Serial.println(httpResponse);
    
  // Free resources
  http.end();
}

void sendExerciseData(void) {
  httpPOSTRequest(cloudServer);
}

void getExerciseData(lv_obj_t *list) {
  exerciseData= httpGETRequest(cloudServer);
  Serial.println(exerciseData);
  JSONVar exerciseObject = JSON.parse(exerciseData);

  if (JSON.typeof(exerciseObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }
  Serial.print("JSON object = ");
  Serial.println(exerciseObject);

  JSONVar keys = exerciseObject.keys();

  for (int i = 0; i < keys.length(); i++) {
    JSONVar exerciseContent = exerciseObject[keys[i]];
    lv_obj_t * element;
    
    String label = "#de1d40 Exercise " + (String) (i+1) + "#\n";
    label += "Name: " + JSON.stringify(exerciseContent["username"]) + "\n";
    label += "Date: " + JSON.stringify(exerciseContent["date"]) + "\n";
    label += "Distance Covered: " + JSON.stringify(exerciseContent["distance"]) + "\n";
    label += "Calories Burned: " + JSON.stringify(exerciseContent["calories"]) + "\n";
    label += "Step Count: " + JSON.stringify(exerciseContent["stepcount"]) + "\n";
    label += "Target Steps: " + JSON.stringify(exerciseContent["targetsteps"]);
    
    element = lv_list_add_btn(list, NULL, NULL); 
    lv_obj_t *listButtonLabel = lv_label_create(element, NULL);
    lv_label_set_recolor(listButtonLabel, true);
    lv_obj_add_style(listButtonLabel, LV_OBJ_PART_MAIN, &buttonLabelStyle);
    lv_label_set_text(listButtonLabel, label.c_str());
  }
}
