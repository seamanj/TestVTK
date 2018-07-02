#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkCommand.h"
#include "vtkProperty.h"




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
    coneActor->GetProperty()->SetColor(0.2, 0.63, 0.79);
    coneActor->GetProperty()->SetDiffuse(0.7);
    coneActor->GetProperty()->SetSpecular(0.4);
    coneActor->GetProperty()->SetSpecularPower(20);


    vtkProperty *property = vtkProperty::New();
    property->SetColor(1.0, 0.3882, 0.2784);
    property->SetDiffuse(0.7);
    property->SetSpecular(0.4);
    property->SetSpecularPower(20);

    vtkActor *coneActor2 = vtkActor::New();
    coneActor2->SetMapper(coneMapper);
    coneActor2->GetProperty()->SetColor(0.2, 0.63, 0.79);
    coneActor2->SetProperty(property);
    coneActor2->SetPosition(0, 2, 0);

    vtkRenderer *ren1= vtkRenderer::New();
    ren1->AddActor( coneActor );
    ren1->AddActor( coneActor2 );
    ren1->SetBackground( 0.1, 0.2, 0.4 );



    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
    renWin->SetSize( 300, 300 );


    int i;
    for(int i = 0; i < 360; ++i)
    {
        renWin->Render();
        ren1->GetActiveCamera()->Azimuth(1);
    }

    cone->Delete();
    coneMapper->Delete();
    coneActor->Delete();
    property->Delete();
    coneActor2->Delete();
    ren1->Delete();
    renWin->Delete();

}
