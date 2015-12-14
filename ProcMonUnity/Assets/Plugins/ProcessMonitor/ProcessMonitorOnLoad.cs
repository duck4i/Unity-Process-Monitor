using UnityEngine;
using System.Collections;

#if UNITY_EDITOR_WIN
using UnityEditor;

[InitializeOnLoad]
public class ProcessMonitorOnLoad 
{
	static ProcessMonitorOnLoad()
    {
        //ProcessMonitor.PM_SetOutputDirectory(Application.dataPath + "/../");
        
        if (ProcessMonitor.PM_Create())
        {
            Debug.Log("ProcessMonitor created");

            if (ProcessMonitor.PM_Enable(true))
            {
                Debug.Log("ProcessMonitor hooks enabled");
            }
            else
            {
                Debug.Log("ProcessMonitor could not hook to Unity");
            }
        }
        else
        {
            Debug.LogWarning("ProcessMonitor could not load");
        }
    }
}

#endif