using UnityEngine;
using System.Collections;

#if UNITY_EDITOR_WIN

using System.Runtime.InteropServices;

public class ProcessMonitor 
{
    [DllImport("ProcMonDLL")]
    public static extern bool PM_Create();

    [DllImport("ProcMonDLL")]
    public static extern bool PM_Destroy();

    [DllImport("ProcMonDLL")]
    public static extern bool PM_Enable(bool enable);
}

#endif