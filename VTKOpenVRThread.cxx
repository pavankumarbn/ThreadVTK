#Author : Pavan Kumar B N
#Date : 22/02/2019
# Description: It creates two thereads for 2 differenet rendering, 1. For normal (Desktop) Rendering, 2. OpenVR Rendering. Also includes, NamedPipe implementation. 


#include <vtkActor.h>
#include <vtkColorTransferFunction.h>
#include <vtkConeSource.h>
#include <vtkDICOMImageReader.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkNew.h>
#include <vtkOpenVRCamera.h>
//#include <vtkOpenVRCustomInteractorStyle.h>
#include <vtkOpenVRInteractorStyle.h>
#include <vtkSTLReader.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPolyDataMapper.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkGeometryFilter.h>
#include <vtkOBJReader.h>
#include <vtkSmartPointer.h>
#include <cmath>
#include <vtkGlyph3D.h>
#include <vtkLODActor.h>
#include <vtkLODActor.h>
#include <vtkPDBReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkColorTransferFunction.h>
#include <vtkConeSource.h>
#include <vtkProperty.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkTextProperty.h>
#include <vtkNew.h>
#include <vtkOpenVRCamera.h>
#include <vtkOpenVRInteractorStyle.h>
#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkSphereSource.h>
#include <vtkTubeFilter.h>
#include <vtkCommand.h>
//#include <vtkEventData.h>
#include <vtkAutoInit.h>
#include <vtkCubeAxesActor.h>
#include <vtkTextActor.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkGeometryFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkCylinderSource.h>
#include <vtkSTLReader.h>
#include <vtkOBJReader.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <vtkCommand.h>
#include <stdio.h>
using namespace std;
#include <sstream>
#include<omp.h>

#include <Windows.h>
#include <iostream>
using namespace std;

HANDLE     hCreatefile = INVALID_HANDLE_VALUE;
BOOL       bCallNamedPipe = TRUE;
DWORD      dwNoBytesRead = 0;
DWORD      dwNoBytesWrite = 0;
BOOL       bReadfile = TRUE;
BOOL       bWritefile = TRUE;
char       szReadFileBuffer[1023] = { 0 };
//char       szWriteFileBuffer[1023] = "Hi";
DWORD      dwReadFileBufferSize = sizeof(szReadFileBuffer);
//DWORD      dwWriteFileBufferSize = sizeof(szWriteFileBuffer);
BOOL       bFlushBuffer = TRUE;
BOOL       bClosehandle = TRUE;



vtkNew<vtkOpenVRRenderWindow> renderWindow;
//vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
int temp = 0;
int flag = 0;
class MyClass
{
public:
	static MyClass *New()
	{
		MyClass *cb = new MyClass;
		return cb;
	}
	void Execute(int i)
	{
			//std::cout << "inside setposition" << std::endl;
			double position[3];
			readerCAD->Update();
			//transform->Scale(0.005, 0.005, 0.005);

			
			transformFilter->SetInputConnection(readerCAD->GetOutputPort());
			transformFilter->SetTransform(transform);

			
			mapperCAD->SetInputConnection(transformFilter->GetOutputPort());

			//vtkSmartPointer<vtkActor> actorCAD = vtkSmartPointer<vtkActor>::New();
			actor->SetMapper(mapperCAD);
			renderer->AddActor(actor);

			renderer->AddActor(actorPCD);

			//actor->SetPosition(-30,5,0);
			//actor->SetPosition(-30, 5, -15);
			//actor->SetOrientation(90, 0, 0);
			//actorPCD->SetPosition(-80, -55, 50);


			actor->GetPosition(position);
			//cout << 'x ' << position[0]<< 'y '<< position[1]<<'z '  << position[2];
			
			switch (i)
				{
				case 2:
					if (flag == -14) {
						actor->SetPosition(-30, 5, -15);
						break;
					}
					else if  (flag > -40)
					{
						actor->SetPosition(-30, 5, flag - 2); 
						//actor->SetPosition(position[0], position[1], position[2] + 1);
						flag = flag -2;
					
						cout << "in case 2" << "\n";
					}
					break;
				case 1: 
					if (flag == -15) {
						actor->SetPosition(-30, 5, -15);
						break;

					}
					else if (flag < 40)
					{
						actor->SetPosition(-30, 5, flag + 2);
						//actor->SetPosition(position[0], position[1], position[2] - 1);
						flag = flag + 2;		
						//transform->Translate(-1000, 0, 0);
						cout << "in case 1" << "\n";
						//renderWindow->Render();
					}
					
					//Sleep(10000);
					break;
				case 3:
					if (position[1] < 100) {
						//actor->SetPosition(0, position[1] + 1, 0);

						//transform->Translate(0, 1000, 0);
						cout << "in case 3" << "\n";
						//renderWindow->Render();
					}
					
					//Sleep(10000);
					break;
				case 4: 
					if (position[1] > -100) {
						//actor->SetPosition(0, position[1] - 1, 0);

						//transform->Translate(0, -1000, 0);
						cout << "in case 4" << "\n";
						//renderWindow->Render();
					}
					
					//Sleep(10000);
					break;
				//default: 
				}
			view = iren->GetPhysicalTranslation(cam);
			//iren->SetPhysicalTranslation(cam, 120, 50, -50);
			iren->SetPhysicalTranslation(cam, -5, 0, 0);
			iren->GetRenderWindow()->Render();
			//Sleep(1000);
		//}
		
	}

private:
	int TimerCount;
public:
	vtkSmartPointer<vtkActor> actor,actorPCD;
	vtkOpenVRRenderWindowInteractor * iren;
	vtkNew<vtkOpenVRCamera> cam;
	vtkSmartPointer<vtkOpenVRRenderer> renderer;
	vtkSmartPointer<vtkTransform> transform;
	vtkSmartPointer<vtkOBJReader> readerCAD;
	vtkSmartPointer<vtkPolyDataMapper> mapperCAD;
	vtkSmartPointer<vtkTransformFilter> transformFilter;
	
	double *view = (double *)malloc(sizeof(double) * 3);
};

int main(int argc, char* argv[])
{

	int x, y, z, gazeInput;

	vtkNew<vtkVolume> volume;
	vtkSmartPointer<vtkOpenVRRenderer> renderer = vtkSmartPointer<vtkOpenVRRenderer>::New();

	vtkNew<vtkOpenVRRenderWindowInteractor> iren;
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	vtkSmartPointer<vtkTransform> transformPCD = vtkSmartPointer<vtkTransform>::New();

	vtkNew<vtkOpenVRInteractorStyle> style;
	vtkNew<vtkOpenVRCamera> cam;

	hCreatefile = CreateFile(
		L"\\\\.\\pipe\\mynamedpipe",
		GENERIC_READ | GENERIC_WRITE,
	 	0,
		NULL,
		OPEN_EXISTING,//CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	
	vtkSmartPointer<vtkUnstructuredGridReader> readerPCD = vtkSmartPointer<vtkUnstructuredGridReader>::New();

	readerPCD->SetFileName("PCD_Down.vtk");
	
	//reader1->SetFileName("FARO_Scan_PlantPart_two.vtk");//FARO_Scan_PlantPart_ninehundred_2 - VTK unstructured grid.vtk
	readerPCD->Update();
	vtkSmartPointer<vtkTransformFilter> transformFilterPCD = vtkSmartPointer<vtkTransformFilter>::New();
	transformFilterPCD->SetInputConnection(readerPCD->GetOutputPort());
	transformFilterPCD->SetTransform(transformPCD);
	
	transformPCD->Scale(0.009, 0.009, 0.009);


	vtkSmartPointer<vtkGeometryFilter> geometryFilterPCD =		vtkSmartPointer<vtkGeometryFilter>::New();
	geometryFilterPCD->SetInputConnection(readerPCD->GetOutputPort());
	geometryFilterPCD->Update();

	vtkSmartPointer<vtkPolyDataMapper> MapperPCD =		vtkSmartPointer<vtkPolyDataMapper>::New();
	MapperPCD->SetInputConnection(geometryFilterPCD->GetOutputPort());

	vtkSmartPointer<vtkActor> actorPCD=		vtkSmartPointer<vtkActor>::New();
	actorPCD->SetMapper(MapperPCD);

	vtkSmartPointer<vtkOBJReader> readerCAD = vtkSmartPointer<vtkOBJReader>::New();
	//reader->SetFileName("pipe_new_2.obj"); //original modelpipe model ver3 //pipe model ver3.obj
	readerCAD->SetFileName("pipe model ver3.obj");  // pipe model ver4.obj

	readerCAD->Update();
	transform->Scale(0.005, 0.005, 0.005);

	vtkSmartPointer<vtkTransformFilter> transformFilter =		vtkSmartPointer<vtkTransformFilter>::New();
	transformFilter->SetInputConnection(readerCAD->GetOutputPort());
	transformFilter->SetTransform(transform);

	vtkSmartPointer<vtkPolyDataMapper> mapperCAD = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperCAD->SetInputConnection(transformFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> actorCAD = vtkSmartPointer<vtkActor>::New();
	actorCAD->SetMapper(mapperCAD);

	double x1[3], origin[3], originA[3];
	actorCAD->GetPosition(x1);

	actorPCD->GetOrigin(origin);
	cout << 'x' << origin[0] << origin[1] << origin[2];
	cout << "xA" << originA[0] << ',' << originA[1] << ',' << originA[2];

	renderer->AddActor(actorPCD);

	renderer->AddActor(actorCAD);
	actorCAD->SetPosition(-30, 5, 0);
	actorCAD->SetOrientation(90, 0, 0);
	actorPCD->SetPosition(-80, 0, 50);
	renderer->SetBackground(0, 0, 0);
	/*double position[3];
	actorCAD->GetPosition(position);
	cout << 'x ' << position[0] << 'y ' << position[1] << 'z ' << position[2];*/

	renderWindow->AddRenderer(renderer);
	iren->SetRenderWindow(renderWindow);
	iren->SetInteractorStyle(style);
	//renderer->SetActiveCamera(cam);
	vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();
	cubeAxesActor->SetCamera(renderer->GetActiveCamera());
	cubeAxesActor->SetBounds(-15, 40, -15, 40, -40, 10);
	cubeAxesActor->GetTitleTextProperty(0)->SetColor(1.0, 0.0, 0.0);
	cubeAxesActor->GetLabelTextProperty(0)->SetColor(1.0, 0.0, 0.0);

	cubeAxesActor->GetTitleTextProperty(1)->SetColor(0.0, 1.0, 0.0);
	cubeAxesActor->GetLabelTextProperty(1)->SetColor(0.0, 1.0, 0.0);

	cubeAxesActor->GetTitleTextProperty(2)->SetColor(0.0, 0.0, 1.0);
	cubeAxesActor->GetLabelTextProperty(2)->SetColor(0.0, 0.0, 1.0);
	cubeAxesActor->SetFlyModeToStaticTriad();

	renderWindow->SetMultiSamples(0);
	double *view = (double *)malloc(sizeof(double) * 3);
	// Render
	renderer->ResetCamera();
	renderWindow->Render();

	Sleep(1000);
	
	if (INVALID_HANDLE_VALUE == hCreatefile)
	{
		cout << "File Creation Failed = " << GetLastError() << endl;
		goto CleanUp;
	}// if
	else
	{
		cout << "File Creation Success" << endl;
	}

	
	omp_set_num_threads(2);
	#pragma omp parallel
	{
		#pragma omp critical		
		{
			cout << "inside criti\n";
			if (temp == 0)
			{
				cout << "inside else loop";
				MyClass* cb = new MyClass;
				//MyClass* cb = reinterpret_cast<MyClass*>(_top);
				cb->actor = actorCAD;
				cb->actorPCD = actorPCD;
				cb->readerCAD = readerCAD;
				cb->renderer = renderer;
				cb->transform = transform;
				cb->transformFilter = transformFilter;
				cb->mapperCAD = mapperCAD;
				//cb->transformFilterPCD = transformFilterPCD;
				cb->iren = iren;
				cout << "before while\n";
				for(;;)
				{
					bReadfile = ReadFile(
						hCreatefile,
						szReadFileBuffer,
						dwReadFileBufferSize,
						&dwNoBytesRead,
						NULL);

					if (strcmp(szReadFileBuffer, "left") == 0) 
						gazeInput = 1;
					if (strcmp(szReadFileBuffer, "right") == 0)
						gazeInput = 2;
					if (strcmp(szReadFileBuffer, "up") == 0)
						gazeInput = 3;
					if (strcmp(szReadFileBuffer, "down") == 0)
						gazeInput = 4;
					if (strcmp(szReadFileBuffer, "no") == 0)
						gazeInput = 0;

					cb->Execute(gazeInput);

					char *begin = szReadFileBuffer;
					char *end = begin + sizeof(szReadFileBuffer);
					std::fill(begin, end, 0);
					
						//Sleep(2000);
				}//end of while
			}// end of if
			else
			{
				//do nothing	
			}
		}//end of omp critical
		//renderWindow->Render();
	}// end of omp parallel
	//}

	/////// For pipe 
CleanUp:
	bClosehandle = CloseHandle(hCreatefile);
	if (TRUE == bClosehandle)
	{
		cout << "CreateFile close Handle Success" << endl;
	}// if
	else
	{
		cout << "CreateFile closeHandle Failed = " << GetLastError() << endl;
	}// else pipe close

	renderWindow->Render();
	view = iren->GetPhysicalTranslation(cam);
	iren->SetPhysicalTranslation(cam, -5, 0, 0);
	iren->Start();
	return EXIT_SUCCESS;
}
