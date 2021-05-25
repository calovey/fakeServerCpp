#ifndef FAKESERVER_H
#define FAKESERVER_H
//#include <nvr/recorder.grpc.pb.h>


class FakeServer: public vms::RecorderService::Service
{
public:
	FakeServer();
	grpc::Status GetRecordDetails(grpc::ServerContext *context, const vms::CameraQ *request, vms::RecordDetails *response) override;
	int start();
};

#endif // FAKESERVER_H
