package org.qtproject.InoCobotTP;

import org.qtproject.qt.android.bindings.QtActivity;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import java.util.List;
import android.net.Uri;
import android.os.Message;
import android.os.Handler;
import android.os.Bundle;
import android.os.PowerManager;
import android.app.ActivityManager;
import android.net.wifi.WifiInfo;
import android.content.Intent;
import android.view.KeyEvent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.provider.Settings;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.os.Build;
import android.provider.MediaStore;

import java.io.File;
import java.io.FileInputStream;
import java.io.OutputStream;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;

import org.qtproject.InoCobotTP.WifiStrengthReceiver;
import org.qtproject.InoCobotTP.JniInterface;

public class InoCobotTP extends org.qtproject.qt.android.bindings.QtActivity
{
    private static InoCobotTP m_instance;
    private WifiManager wifiManager;
	private WifiStrengthReceiver receiver;
	private IntentFilter filter;
    // List<ScanResult> listb;
    public InoCobotTP() {
        m_instance = this;
    }
	
	@Override  
	public void onWindowFocusChanged(boolean hasFocus) {  
		 super.onWindowFocusChanged(hasFocus);  
		 if (hasFocus) {  
			System.out.println("java activity : onWindowFocusChanged");
			new JniInterface().refreshWifiName();
			new JniInterface().activityResume();
		 } else {
			
		 }
	} 
	
	@Override
    protected void onResume() {
        super.onResume();
    }
 
    @Override
    protected void onPause() {
        super.onPause();
		new JniInterface().activityPause();
    }
	
	@Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            // Toast.makeText(this, "回退键被按下", Toast.LENGTH_SHORT).show();
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
	
    public String getWifiName()
    {
        System.out.println("Call Java Jni Function(getWifiName)");
        wifiManager = (WifiManager)getSystemService(WIFI_SERVICE);
        if(!wifiManager.isWifiEnabled()){
            if(wifiManager.getWifiState() != WifiManager.WIFI_STATE_ENABLING) {
                wifiManager.setWifiEnabled(true);
            }
        }

        WifiInfo wifiInfo = wifiManager.getConnectionInfo();
        System.out.println(wifiInfo.getSSID());
        return wifiInfo.getSSID();
    }
	
    public String getDeviceModel() {
        return Build.MODEL;
    }

    public int getWifiStrength()
    {
        System.out.println("Call Java Jni Function(getWifiStrength)");
        wifiManager = (WifiManager)getSystemService(WIFI_SERVICE);
        if(!wifiManager.isWifiEnabled()){
            if(wifiManager.getWifiState() != WifiManager.WIFI_STATE_ENABLING) {
                wifiManager.setWifiEnabled(true);
            }
        }

        int wifiStrength = wifiManager.getConnectionInfo().getRssi();
        System.out.println(wifiStrength);
        return wifiStrength;
    }

    public void openSystemWifi()
    {
        Intent wifiSettingsIntent = new Intent("android.settings.WIFI_SETTINGS");
        startActivity(wifiSettingsIntent);
    }
	
	public void registWifiListenerCb()
	{
		// System.loadLibrary("JniInterface");
		
		receiver = new WifiStrengthReceiver();
		filter = new IntentFilter();
		filter.addAction(WifiManager.RSSI_CHANGED_ACTION);
		filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
		registerReceiver(receiver, filter);
	}
	
	public boolean isIgnoringBatteryOptimizations()
	{
		boolean isIgnoring = false;
		PowerManager powerManager = (PowerManager) getSystemService(POWER_SERVICE);

		if (powerManager != null) {
			System.out.println("[isIgnoringBatteryOptimizations]");
			isIgnoring = powerManager.isIgnoringBatteryOptimizations(getPackageName());
		}

		 return isIgnoring;
	}
	
	public void requestIgnoreBatteryOptimizations()
	{
		try {
			System.out.println("[requestIgnoreBatteryOptimizations]start activity.");
			Intent intent = new Intent(Settings.ACTION_REQUEST_IGNORE_BATTERY_OPTIMIZATIONS);
			intent.setData(Uri.parse("package:" + getPackageName()));
			startActivity(intent);
		}catch (Exception e){
			e.printStackTrace();
		}
	}
	
	public void openTaskLock()
	{
		ActivityManager am = (ActivityManager)getSystemService(ACTIVITY_SERVICE);
		if (am.getLockTaskModeState() != ActivityManager.LOCK_TASK_MODE_NONE) {
			return;
		} 
		startLockTask();
	}
	
	public void installApk(String apkPath)
    {
		Uri uri = Uri.parse(apkPath);
		Intent intent = new Intent(Intent.ACTION_VIEW);
		intent.setDataAndType(uri, "application/vnd.android.package-archive");
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
		startActivity(intent);		
    }

    public boolean copyFileToFolder(String sourceFilePath, String destFilePath) {
        boolean isOk = false;

        File sourceFile = new File(sourceFilePath);
        if (!sourceFile.exists()) {
            System.out.println("[copyFileToFolder]Source file does not exist.");
            return isOk;
        }

        String destinationFileName = new File(destFilePath).getName();
        String destinationRelativePath = new File(destFilePath).getParent();

        ContentValues contentValues = new ContentValues();
        contentValues.put(MediaStore.MediaColumns.DISPLAY_NAME, destinationFileName);
        contentValues.put(MediaStore.MediaColumns.MIME_TYPE, "application/octet-stream");
        contentValues.put(MediaStore.MediaColumns.RELATIVE_PATH, destinationRelativePath);

        Uri uri = getContentResolver().insert(MediaStore.Files.getContentUri("external"), contentValues);
        if (uri == null) {
            System.out.println("[copyFileToFolder]Failed to create new MediaStore record.");
            return isOk;
        }

        try (OutputStream outputStream = getContentResolver().openOutputStream(uri);
            FileInputStream inputStream = new FileInputStream(sourceFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }

            System.out.println("[copyFileToFolder]Success to copy file.");
            isOk = true;
        } catch (Exception e) {
            System.out.println("[copyFileToFolder]Failed to copy file.");
            isOk = false;
        }

        return isOk;
    }

    public String getAppVersionName() {
        String versionName = "";
        try {
            PackageManager packageManager = getPackageManager();
            String packageName = getPackageName();
            PackageInfo packageInfo = packageManager.getPackageInfo(packageName, 0);
            versionName = packageInfo.versionName;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }

        return versionName;
    }

    public String getOldAppPath() {
        String  path = getApplicationInfo().sourceDir;
        return path;
    }

    public boolean generateUpgradePatch(String patchFilePath, String newAppPath) {
        String oldAppPath = getOldAppPath();
        if (oldAppPath == null || oldAppPath.isEmpty()) {
            System.out.println("[generateUpgradePatch]Failed to get old app file.");
            return false;
        }

        if (newAppPath == null || newAppPath.isEmpty()) {
            System.out.println("[generateUpgradePatch]Failed to get new app file.");
            return false;
        }

        // oldAppPath = "/storage/emulated/0/Android/data/org.qtproject.InoCobotTP/files/share/studio/old.apk";
        // newAppPath = "/storage/emulated/0/Android/data/org.qtproject.InoCobotTP/files/share/studio/new.apk";
        // patchFilePath = "/storage/emulated/0/Android/data/org.qtproject.InoCobotTP/files/share/studio/upgrade.patch";

        return new JniInterface().makeDiff(oldAppPath, newAppPath, patchFilePath);
    }

    public boolean generateUpgradeApp(String patchFilePath, String newAppPath) {
        String oldAppPath = getOldAppPath();
        if (oldAppPath == null || oldAppPath.isEmpty()) {
            System.out.println("[generateUpgradeApp]Failed to get old app file.");
            return false;
        }

        if (newAppPath == null || newAppPath.isEmpty()) {
            System.out.println("[generateUpgradeApp]Failed to get new app file.");
            return false;
        }

        return new JniInterface().applyPatch(oldAppPath, newAppPath, patchFilePath);
    }
}
