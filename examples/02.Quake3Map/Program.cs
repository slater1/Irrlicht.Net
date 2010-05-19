﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _02.Quake3Map
{
	class Program
	{
		static void Main(string[] args)
		{
			DriverType driverType;

			Console.Write("Please select the driver you want for this example:\n" +
						" (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n" +
						" (d) Burning's Software Renderer\n (e) Software Renderer\n" +
						" (f) NullDevice\n (otherKey) exit\n\n");

			ConsoleKeyInfo i = Console.ReadKey();

			switch (i.Key)
			{
				case ConsoleKey.A: driverType = DriverType.OpenGL; break;
				case ConsoleKey.B: driverType = DriverType.Direct3D9; break;
				case ConsoleKey.C: driverType = DriverType.Direct3D8; break;
				case ConsoleKey.D: driverType = DriverType.BurningsVideo; break;
				case ConsoleKey.E: driverType = DriverType.Software; break;
				case ConsoleKey.F: driverType = DriverType.Null; break;
				default:
					return;
			}

			IrrlichtDevice device =
				IrrlichtDevice.CreateDevice(driverType, new Dimension2Du(640, 480));

			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager scene = device.SceneManager;

			device.FileSystem.AddFileArchive("../media/map-20kdm2.pk3");

			AnimatedMesh mesh = scene.GetMesh("20kdm2.bsp");
			SceneNode node = null;

			if (mesh != null)
				node = scene.AddOctreeSceneNode(mesh.GetMesh(0), null, -1, 1024);

			if (node != null)
				node.Position = new Vector3Df(-1300, -144, -1249);

			scene.AddCameraSceneNodeFPS();

			device.CursorControl.Visible = false;

			int lastFPS = -1;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					driver.BeginScene(true, true, new Coloru(255, 200, 200, 200));
					scene.DrawAll();
					driver.EndScene();

					int fps = driver.FPS;
					if (lastFPS != fps)
					{
						device.WindowCaption = String.Format(
							"Irrlicht Engine - Quake 3 Map example [{0}] FPS:{1}",
							driver.Name, fps);

						lastFPS = fps;
					}
				}
			}
		}
	}
}
