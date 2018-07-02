#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkCommand.h"
#include "vtkBoxWidget.h"
#include "vtkTransform.h"
#include "vtkInteractorStyleTrackballCamera.h"

class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
    { return new vtkMyCallback; }
  void Execute(vtkObject *caller, unsigned long, void*) override
  {
      vtkTransform *t = vtkTransform::New();
      vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
      widget->GetTransform(t);
      widget->GetProp3D()->SetUserTransform(t);
      t->Delete();
  }
};


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


    vtkRenderer *ren1= vtkRenderer::New();
    ren1->AddActor( coneActor );
    ren1->SetBackground( 0.1, 0.2, 0.4 );



    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
    renWin->SetSize( 300, 300 );

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

    vtkInteractorStyleTrackballCamera *style =
      vtkInteractorStyleTrackballCamera::New();
    iren->SetInteractorStyle(style);


    vtkBoxWidget *boxWidget = vtkBoxWidget::New();
    boxWidget->SetInteractor(iren);
    boxWidget->SetPlaceFactor(1.25);

    boxWidget->SetProp3D(coneActor);
    boxWidget->PlaceWidget();
    vtkMyCallback *callback = vtkMyCallback::New();
    boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

    boxWidget->On();


    iren->Initialize();
    iren->Start();


    cone->Delete();
    coneMapper->Delete();
    coneActor->Delete();
    callback->Delete();
    boxWidget->Delete();
    ren1->Delete();
    renWin->Delete();
    iren->Delete();
    style->Delete();

    return 0;
}
