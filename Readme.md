Unity Process Monitor
---

#### What and why?

Unity Editor DLL injection plugin for montioring external process calls on Windows.

I needed a tool that can inspect all outgoing CreateProcess calls for some benchmarking, so I created this tool as a sample.

Current implementation is printing out all calls, plus it paches all PVRTextureTool calls and lowers the quality setting requested by Unity so the builds are faster, but of course with more artifacts.
Pached calls are done for PVRTC and ETC1 textures.

#### Install

You can install this plugin easily, just double click on **ProcMonUnity/Packages/ProcessMonitor.unitypackage** from this repo.

##### PVRTexTool (patched) calls:

```
"PVRTexTool.exe" "-flip" "y" "-f" "PVRTC1_4_RGB" "-q" "pvrtcnormal" "-i" "Temp\188439b1162b7f34ba45b10d902fa2c6-feed.png" "-o" "Temp\188439b1162b7f34ba45b10d902fa2c6-res.pvr"
Patching PVRTC ....
"PVRTexTool.exe" "-flip" "y" "-f" "PVRTC1_4_RGB" "-q" "pvrtcfastest" "-i" "Temp\188439b1162b7f34ba45b10d902fa2c6-feed.png" "-o" "Temp\188439b1162b7f34ba45b10d902fa2c6-res.pvr"
```

##### Other printouts:


```
//	Shader compiler calls
Hooker::Hook New process:
"UnityShaderCompiler.exe" "Unity/Editor/Data" "./Library/shadercompiler-32bit-1.log" "\\.\pipe\UnityShaderCompiler-32bit-1-2472" "C:/Users_USE_MATH_DEFINES;WIN32;_WINDOWS;Desktop/Unity 5.1.4f1/Unity/Editor/Data/PlaybackEngines"
```

```
//	Perforce integration calls often look like this
"Unity\Editor\Data\Tools\VersionControl\PerforcePlugin.exe"
```

```
//	Calculating GI calls
"Unity\Editor\Data\Tools64\JobProcess.exe" "C:/Users_USE_MATH_DEFINES;WIN32;_WINDOWS;Desktop/Perforce/HSX/Main" "Temp/ProcessJobs/e9a6970f79cd12d8b075e7d72f1b07cb.bakert" "Temp/ProcessJobs" "Bake Runtime" "1376" "\\.\pipe\JobProcess-1-5720" "C:/Users_USE_MATH_DEFINES;WIN32;_WINDOWS;AppData/LocalLow/Unity/Caches/GiCache" "0"

//	Or even reporting and licencing
"Unity/Editor/UnityHelper.exe" --type=gpu-process --channel="1376.0.1751763819\770736183" --no-sandbox --lang=en-US --log-severity=disable --user-agent="Mozilla/5.0 (Windows; Win64; ) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.94 Safari/537.36Unity/5.2.3p1 (unity3d.com)" --supports-dual-gpus=false --gpu-driver-bug-workarounds=1,17,44 --gpu-vendor-id=0x10de --gpu-device-id=0x1287 --gpu-driver-vendor=NVIDIA --gpu-driver-version=10.18.13.5362 --lang=en-US --log-severity=disable --user-agent="Mozilla/5.0 (Windows; Win64; ) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.94 Safari/537.36Unity/5.2.3p1 (unity3d.com)" /prefetch:822062411
```
