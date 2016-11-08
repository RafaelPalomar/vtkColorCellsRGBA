/*===============================================================================

  Project: vtkColorCellsRGBA
  Module: main.cxx

  Copyright (c) 2016, Rafael Palomar <rafaelpalomaravalos@gmail.com>

  All rights reserved. This is propietary software. In no event shall the author
  be liable for any claim or damages

  ===============================================================================*/

// VTK includes
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkUnsignedCharArray.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkCellData.h>
#include <vtkXMLPolyDataWriter.h>

//STD includes
#include <iostream>

int main(int argc, char **argv)
{

  if (argc != 2)
    {
    std::cerr << "Invalid number of arguments" << std::endl;
    std::cerr << "Usage: " << argv[0] << "<output_name>.vtp" << std::endl;
    return EXIT_FAILURE;
    }


  // Create a 3D sphere
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->Update();

  // Cell data
  vtkSmartPointer<vtkUnsignedCharArray> cellData =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  cellData->SetNumberOfComponents(4);
  cellData->SetNumberOfTuples(sphere->GetOutput()->GetNumberOfCells());

  // Assign random colors to cell data
  for(int i=0; i<sphere->GetOutput()->GetNumberOfCells(); ++i)
    {
    float color_rgba[4];
    color_rgba[0] = vtkMath::Random(64, 255);
    color_rgba[1] = vtkMath::Random(64, 255);
    color_rgba[2] = vtkMath::Random(64, 255);
    color_rgba[3] = vtkMath::Random(64, 255);
    cellData->InsertTuple(i, color_rgba);
    }
  sphere->GetOutput()->GetCellData()->SetScalars(cellData);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
  renderWindow->Render();
  interactor->Start();

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputData(sphere->GetOutput());
  writer->SetFileName(argv[1]);
  writer->Update();


  return EXIT_SUCCESS;
}
