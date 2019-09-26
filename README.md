# Darknet_Wrapper

This is a class that wraps a darknet network into an easier to use format.
Use is as follows:

```C++
#include "Darknet/Darknet.hpp"

...

net = Darknet(modelConfig, modelWeights, modelNames);

std::vector<std::pair<std::string, cv::Rect> > results = net.Predict(image);
```

