/*
 *  Copyright (c) 2022 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef TEST_PC_E2E_ANALYZER_VIDEO_ANALYZING_VIDEO_SINK_H_
#define TEST_PC_E2E_ANALYZER_VIDEO_ANALYZING_VIDEO_SINK_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "api/test/peerconnection_quality_test_fixture.h"
#include "api/test/video/video_frame_writer.h"
#include "api/test/video_quality_analyzer_interface.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "rtc_base/synchronization/mutex.h"
#include "rtc_base/thread_annotations.h"
#include "system_wrappers/include/clock.h"
#include "test/pc/e2e/analyzer/video/analyzing_video_sinks_helper.h"

namespace webrtc {
namespace webrtc_pc_e2e {

// A sink to inject video quality analyzer as a sink into WebRTC.
class AnalyzingVideoSink : public rtc::VideoSinkInterface<VideoFrame> {
 public:
  AnalyzingVideoSink(
      absl::string_view peer_name,
      Clock* clock,
      VideoQualityAnalyzerInterface& analyzer,
      AnalyzingVideoSinksHelper& sinks_helper,
      const PeerConnectionE2EQualityTestFixture::VideoSubscription&
          subscription);

  // Updates subscription used by this peer to render received video.
  void UpdateSubscription(
      const PeerConnectionE2EQualityTestFixture::VideoSubscription&
          subscription);

  void OnFrame(const VideoFrame& frame) override;

 private:
  struct SinksDescriptor {
    SinksDescriptor(
        absl::string_view sender_peer_name,
        const PeerConnectionE2EQualityTestFixture::VideoResolution& resolution)
        : sender_peer_name(sender_peer_name), resolution(resolution) {}

    // Required to be able to resolve resolutions on new subscription and
    // understand if we need to recreate `video_frame_writer` and `sinks`.
    std::string sender_peer_name;
    // Resolution which was used to create `video_frame_writer` and `sinks`.
    PeerConnectionE2EQualityTestFixture::VideoResolution resolution;

    // Is set if dumping of output video was requested;
    test::VideoFrameWriter* video_frame_writer = nullptr;
    std::vector<std::unique_ptr<rtc::VideoSinkInterface<VideoFrame>>> sinks;
  };

  // Scales video frame to `required_resolution` if necessary. Crashes if video
  // frame and `required_resolution` have different aspect ratio.
  VideoFrame ScaleVideoFrame(
      const VideoFrame& frame,
      const PeerConnectionE2EQualityTestFixture::VideoResolution&
          required_resolution);
  // Creates full copy of the frame to free any frame owned internal buffers
  // and passes created copy to analyzer. Uses `I420Buffer` to represent
  // frame content.
  void AnalyzeFrame(const VideoFrame& frame);
  // Populates sink for specified stream and caches them in `stream_sinks_`.
  SinksDescriptor* PopulateSinks(absl::string_view stream_label);

  const std::string peer_name_;
  Clock* const clock_;
  VideoQualityAnalyzerInterface* const analyzer_;
  AnalyzingVideoSinksHelper* const sinks_helper_;

  Mutex mutex_;
  PeerConnectionE2EQualityTestFixture::VideoSubscription subscription_
      RTC_GUARDED_BY(mutex_);
  std::map<std::string, SinksDescriptor> stream_sinks_ RTC_GUARDED_BY(mutex_);
};

}  // namespace webrtc_pc_e2e
}  // namespace webrtc

#endif  // TEST_PC_E2E_ANALYZER_VIDEO_ANALYZING_VIDEO_SINK_H_
