#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"



int main()
{
    vtkConeSource *cone = vtkConeSource::New();
    cone->SetHeight(3.0);
    cone->SetRadius(1.0);
    cone->SetResolution(10);

    vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
    coneMapper->SetInputConnection(cone->GetOutputPort());

    vtkActor *coneActor = vtkActor::New();
    coneActor->SetMapper(coneMapper);

    vtkRenderer *ren1 = vtkRenderer::New();
    ren1->AddActor(coneActor);
    ren1->SetBackground(0.1, 0.2, 0.4);


    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
    renWin->SetSize(300, 300);

    int i;
    for(int i = 0; i < 360; ++i)
    {
        renWin->Render();
        ren1->GetActiveCamera()->Azimuth(1);
    }

    cone->Delete();
    coneMapper->Delete();
    coneActor->Delete();
    ren1->Delete();
    renWin->Delete();

}
