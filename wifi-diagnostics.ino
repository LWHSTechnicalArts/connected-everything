void setup() {
    Serial.begin(115200);
    WiFi.connect();
    delay(5000);
}

void loop() {
    Serial.println("------------CURRENT WIFI STATUS---------------");

    Serial.print("Internet Connection = ");
    Serial.println(WiFi.ready());
    Serial.print("Connected to network = ");
    Serial.println(WiFi.SSID());
    Serial.print("Signal strength = ");
    Serial.println(WiFi.RSSI());
    Serial.println();
    Serial.println("------------STORED CREDENTIALS---------------");

    WiFiAccessPoint ap[5];
        int found = WiFi.getCredentials(ap, 5);
        for (int i = 0; i < found; i++) {
            Serial.print("ssid: ");
            Serial.println(ap[i].ssid);
            // security is one of WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA, WLAN_SEC_WPA2
            Serial.print("security: ");
            Serial.println(ap[i].security);
            // cipher is one of WLAN_CIPHER_AES, WLAN_CIPHER_TKIP
            Serial.print("cipher: ");
            Serial.println(ap[i].cipher);
        }
     Serial.println("------------END---------------");
    delay(30000);
}
