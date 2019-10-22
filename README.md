# Darknet_Wrapper

This is a class that wraps a darknet network into an easier to use format.
Use is as follows:

```C++
#include "Darknet/Darknet.hpp"

...

net = Darknet(modelConfig, modelWeights, modelNames);

// Predictions are of form <ClassName, BoundingBox, Confidence>
std::vector<std::tuple<std::string, cv::Rect, double> > results = net.Predict(image);
```

