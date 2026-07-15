package org.qtproject.InoCobotTP;
import android.net.wifi.WifiManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;

import org.qtproject.InoCobotTP.JniInterface;

public class WifiStrengthReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        if (WifiManager.RSSI_CHANGED_ACTION.equals(intent.getAction())) {
            WifiManager wifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
            WifiInfo wifiInfo = wifiManager.getConnectionInfo();
            int rssi = wifiInfo.getRssi();
			System.out.println("android broadcast received : wifi rssi changed : " + rssi);
			new JniInterface().refreshWifiStrength();
        }
		if (ConnectivityManager.CONNECTIVITY_ACTION.equals(intent.getAction())) {
            System.out.println("android broadcast received : wifi connected status changed.");
			new JniInterface().refreshWifiName();
        }
    }
}