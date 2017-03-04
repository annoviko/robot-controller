#include "Controller.hpp"

#include "StringConverter.hpp"
#include "SystemExecutor.hpp"

#include <cstring>
#include <iostream>
#include <cerrno>


Controller::Controller(const std::string & pDevice) : Controller() {
    mDevice = pDevice;

    std::cout << "Device: " << pDevice << std::endl;
}


void Controller::Action(const RobotRequest pRequest) {
    mRequest.store((unsigned char) pRequest);
}


void Controller::Speed(const unsigned char pSpeed) {
    std::cout << (unsigned char) ENGINE_SPEED << " " << pSpeed << std::endl;
    std::string request = "sudo echo -n -e '" + ByteConverter::to_hex((unsigned char) ENGINE_SPEED) + ByteConverter::to_hex(pSpeed) + "' > " + mDevice;

    {
        std::lock_guard<std::mutex> guard(mLock);
        SystemExecutor::execute(request);
    }

    std::cout << "Send request '" << request << "'." << std::endl;
}


void Controller::Start(void) {
    mStopFlag = false;
    mController = std::thread(&Controller::ThreadRunner, this);
}


void Controller::Stop(void) {
    mStopFlag = true;
    mController.join();

    std::string request = "sudo echo -n -e '" + ByteConverter::to_hex((unsigned char) STOP) + "' > " + mDevice;
    SystemExecutor::execute(request);
}


void Controller::ThreadRunner(void) {
    std::cout << "Robot Controller is started..." << std::endl;

    while(!mStopFlag) {
        mState = mRequest.load();
        //mRequest.store(STOP);

        std::string request = "sudo echo -n -e '" + ByteConverter::to_hex(mState) + "' > " + mDevice;
        {
            std::lock_guard<std::mutex> guard(mLock);

            SystemExecutor::execute(request);
            std::cout << "Send request '" << request << "'." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "Robot Controller is terminated..." << std::endl;
}
