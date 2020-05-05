#include "pch.h"
#include "App.h"

#include <ppltasks.h>

using namespace hello;

using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

using Microsoft::WRL::ComPtr;

// DirectX 12 ���� ���α׷� ���ø��� ���� ������ https://go.microsoft.com/fwlink/?LinkID=613670&clcid=0x412�� ���� �ֽ��ϴ�.

// main �Լ��� IFrameworkView Ŭ���� �ʱ�ȭ���� ���˴ϴ�.
[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	auto direct3DApplicationSource = ref new Direct3DApplicationSource();
	CoreApplication::Run(direct3DApplicationSource);
	return 0;
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
	return ref new App();
}

App::App() :
	m_windowClosed(false),
	m_windowVisible(true)
{
}

// IFrameworkView�� ���� �� ȣ��Ǵ� ù ��° �޼����Դϴ�.
void App::Initialize(CoreApplicationView^ applicationView)
{
	// ���� ���α׷� ���� �ֱ��� �̺�Ʈ ó���⸦ ����մϴ�. �� ������ Activated�� ���ԵǹǷ�
	// CoreWindow�� Ȱ�� ���·� ����� â���� �������� ������ �� �ֽ��ϴ�.
	applicationView->Activated +=
		ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);

	CoreApplication::Suspending +=
		ref new EventHandler<SuspendingEventArgs^>(this, &App::OnSuspending);

	CoreApplication::Resuming +=
		ref new EventHandler<Platform::Object^>(this, &App::OnResuming);
}

// CoreWindow ��ü�� ����(�Ǵ� �ٽ� ����)�� �� ȣ��˴ϴ�.
void App::SetWindow(CoreWindow^ window)
{
	window->SizeChanged += 
		ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &App::OnWindowSizeChanged);

	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &App::OnVisibilityChanged);

	window->Closed += 
		ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &App::OnWindowClosed);

	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	currentDisplayInformation->DpiChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &App::OnDpiChanged);

	currentDisplayInformation->OrientationChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &App::OnOrientationChanged);

	DisplayInformation::DisplayContentsInvalidated +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &App::OnDisplayContentsInvalidated);
}

// ��� ���ҽ��� �ʱ�ȭ�ϰų� ������ ������ ���� ���α׷� ���¸� �ε��մϴ�.
void App::Load(Platform::String^ entryPoint)
{
	if (m_main == nullptr)
	{
		m_main = std::unique_ptr<helloMain>(new helloMain());
	}
}

// �� �޼���� â�� Ȱ��ȭ�� �� ȣ��˴ϴ�.
void App::Run()
{
	while (!m_windowClosed)
	{
		if (m_windowVisible)
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

			auto commandQueue = GetDeviceResources()->GetCommandQueue();
			PIXBeginEvent(commandQueue, 0, L"Update");
			{
				m_main->Update();
			}
			PIXEndEvent(commandQueue);

			PIXBeginEvent(commandQueue, 0, L"Render");
			{
				if (m_main->Render())
				{
					GetDeviceResources()->Present();
				}
			}
			PIXEndEvent(commandQueue);
		}
		else
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
		}
	}
}

// IFrameworkView�� �ʿ��մϴ�.
// ���� �̺�Ʈ�� Uninitialize�� ȣ������ �ʽ��ϴ�. Uninitialize��
// ���� ���濡 �ִ� ���� IFrameworkView Ŭ������ �����Ǵ� ��쿡 ȣ��˴ϴ�.
void App::Uninitialize()
{
}

// ���� ���α׷� ���� �ֱ� �̺�Ʈ ó�����Դϴ�.

void App::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
	// CoreWindow�� Ȱ��ȭ�Ǿ�� Run()�� ���۵˴ϴ�.
	CoreWindow::GetForCurrentThread()->Activate();
}

void App::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
	// ������ ��û�� �� ���� ���α׷� ���¸� �񵿱������� �����մϴ�. ������ ��ӵǴ� ����
	// ���� ���α׷��� �Ͻ� �ߴ� ���� �۾��� �����ϴ� ���̶�� �ǹ��Դϴ�.
	// ������ ������ ���ӵ��� ���� ���� �ֽ��ϴ�. �� 5�� ��.
	//���� ������ ����˴ϴ�.
	SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

	create_task([this, deferral]()
	{
		m_main->OnSuspending();
		deferral->Complete();
	});
}

void App::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// �Ͻ� �ߴ� �� ��ε�� ��� ������ �Ǵ� ���¸� �����մϴ�. �⺻������ ������
	// �� ���´� �Ͻ� �ߴ� ���� �ٽ� ������ �� �����˴ϴ�. �� �̺�Ʈ��
	// ���� ���α׷��� ������ ������ ��� �߻����� �ʽ��ϴ�.

	m_main->OnResuming();
}

// â �̺�Ʈ ó�����Դϴ�.

void App::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
	GetDeviceResources()->SetLogicalSize(Size(sender->Bounds.Width, sender->Bounds.Height));
	m_main->OnWindowSizeChanged();
}

void App::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void App::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

// DisplayInformation �̺�Ʈ ó�����Դϴ�.

void App::OnDpiChanged(DisplayInformation^ sender, Object^ args)
{
	// ����: ���⿡�� �˻��� LogicalDpi�� ���� ���ػ� ��ġ������ ũ�Ⱑ �����Ǵ� ���
	// ���� ��ȿ DPI�� ��ġ���� ���� �� �ֽ��ϴ�. DPI�� DeviceResources���� �����Ǹ�
	// �׻� GetDpi �޼��带 ����Ͽ� DPI�� �˻��ؾ� �մϴ�.
	// �ڼ��� ������ DeviceResources.cpp�� �����ϼ���.
	GetDeviceResources()->SetDpi(sender->LogicalDpi);
	m_main->OnWindowSizeChanged();
}

void App::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
	GetDeviceResources()->SetCurrentOrientation(sender->CurrentOrientation);
	m_main->OnWindowSizeChanged();
}

void App::OnDisplayContentsInvalidated(DisplayInformation^ sender, Object^ args)
{
	GetDeviceResources()->ValidateDevice();
}

std::shared_ptr<DX::DeviceResources> App::GetDeviceResources()
{
	if (m_deviceResources != nullptr && m_deviceResources->IsDeviceRemoved())
	{
		//���� D3D ��ġ�� ���� ��� ������ �� ��ġ ���� �������ؾ� �մϴ�.
		// ���� �� �ֽ��ϴ�.

		m_deviceResources = nullptr;
		m_main->OnDeviceRemoved();

#if defined(_DEBUG)
		ComPtr<IDXGIDebug1> dxgiDebug;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug))))
		{
			dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
		}
#endif
	}

	if (m_deviceResources == nullptr)
	{
		m_deviceResources = std::make_shared<DX::DeviceResources>();
		m_deviceResources->SetWindow(CoreWindow::GetForCurrentThread());
		m_main->CreateRenderers(m_deviceResources);
	}
	return m_deviceResources;
}
