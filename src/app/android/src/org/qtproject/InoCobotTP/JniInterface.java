package org.qtproject.InoCobotTP;

public class JniInterface {
	static {
		System.loadLibrary("JniInterface");
	}
	
    public native void refreshWifiStrength();
	public native void refreshWifiName();
	public native void activityPause();
	public native void activityResume();
	public native void backPressed();
	public native boolean makeDiff(String oldFilePath, String newFilePath, String patchFilePath);
	public native boolean applyPatch(String oldFilePath, String newFilePath, String patchFilePath);
}