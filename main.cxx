/*===============================================================================

  Project: vtkColorCellsRGBA
  Module: main.cxx

  Copyright (c) 2016, Rafael Palomar <rafaelpalomaravalos@gmail.com>

  All rights reserved. This is propietary software. In no event shall the author
  be liable for any claim or damages

  ===============================================================================*/

// VTK includes
#include <vtkNew.h>
#include <vtkUnsignedCharArray.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkCellData.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>

//STD includes
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{

  if (argc != 7)
    {
    std::cerr << "Invalid number of arguments" << std::endl;
    std::cerr << "Usage: " << argv[0]
              << "<input_file>.vtk"
              << "<red_component>"
              << "<green_component>"
              << "<blue_component>"
              << "<alpha_component>"
              << "<output_name>.vtk" << std::endl;
    return EXIT_FAILURE;
    }

  // Read the input data
  vtkNew<vtkPolyDataReader> reader;
  reader->SetFileName(argv[1]);
  reader->Update();

  // Cell data
  vtkNew<vtkUnsignedCharArray> cellData;
  cellData->SetNumberOfComponents(4);
  cellData->SetNumberOfTuples(reader->GetOutput()->GetNumberOfCells());

  // Assign random colors to cell data
  for(int i=0; i<reader->GetOutput()->GetNumberOfCells(); ++i)
    {
    float color_rgba[4];
    color_rgba[0] = atoi(argv[2]);
    color_rgba[1] = atoi(argv[3]);
    color_rgba[2] = atoi(argv[4]);
    color_rgba[3] = atoi(argv[5]);
    cellData->InsertTuple(i, color_rgba);
    }
  reader->GetOutput()->GetCellData()->SetScalars(cellData.GetPointer());

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputData(reader->GetOutput());

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper.GetPointer());

  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer.GetPointer());

  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow(renderWindow.GetPointer());
  renderer->AddActor(actor.GetPointer());
  renderWindow->Render();
  interactor->Start();

  vtkNew<vtkPolyDataWriter> writer;
  writer->SetInputData(reader->GetOutput());
  writer->SetFileName(argv[6]);
  writer->Update();


  return EXIT_SUCCESS;
}
