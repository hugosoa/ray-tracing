# Discovery report

## Problem statement

A large 3D animation studio needs its own ray tracer that it can trust, maintain and extend for years, because its current rendering tools produce black artifacts, got twice as slow and cost 2 million per year in licences, but the studio has no documentation or version control to build and maintain this kind of software.

## Client interview summary

**Need:** The client needs a ray tracer to render 3D animated films. It must be fast enough and reliable for years, and keep working long after it is delivered. The studio has learned from its past mistakes and wants a ray tracer that is readable, tested and documented.

### Current situation and pain points

> **Q (Team):** "What do you use to render your films today?"
>
> **A:** "We render with Maya today."

> **Q (Team):** "When did the rendering tools start to break?"
>
> **A:** "6 months ago, on a big project."

> **Q (Team):** "Why do you say that the rendering tools are broken?"
>
> **A:** "Black artifacts appear in the images and the render time doubled."

> **Q (Team):** "How is the code of your current tools documented?"
>
> **A:** "There is no documentation format."

> **Q (Team):** "Do you use a version control tool for your code?"
>
> **A:** "No, we have no code manager like Git."

**My conclusion:** The current pipeline is unreliable (visual bugs, slower renders) and the studio has no engineering practices (no documentation, no version control). The new ray tracer must come with these practices from day one.

### Why an in-house ray tracer

> **Q (Team):** "Why not buy an existing render engine on the market?"
>
> **A:** "Licences on the market are too expensive."

> **Q (Team):** "How much do you spend on licences today?"
>
> **A:** "2 million per year. Licences are paid per computer, so an in-house solution will cost less to the company."

> **Q (Team):** "What is missing in Maya for your needs?"
>
> **A:** "We want a proper ray tracer we can add features to. Maya is expensive and doesn't allow this."

> **Q (Team):** "Who will maintain the solution once it is delivered?"
>
> **A:** "We want to maintain the solution in-house."

> **Q (Team):** "Do you have constraints on the licence of the tools and libraries we use?"
>
> **A:** "Open source."

> **Q (Team):** "Free open-source render engines already exist (Cycles, pbrt, LuxCoreRender). Why not use or extend one of them?"
>
> **A:** "With an open-source project, we depend on the community to fix the problems, and from our experience it can take a long time. We want to be the owner of the ray tracer."

> **Q (Team):** "Is Maya only used for rendering, or also for modelling and animation?"
>
> **A:** "Many machines run Maya only for rendering. Only 10 licences are used for modelling."

**My conclusion:** The main drivers are cost and control: the studio wants to own the code, extend it and maintain it itself, without waiting for an external community to fix bugs. The code must be readable and documented enough for their team to take it over. Since most Maya licences are used only for rendering, replacing the renderer will remove most of the licence cost: only the 10 modelling licences will remain.

### Rendering requirements

> **Q (Team):** "What kind of content will the ray tracer have to render?"
>
> **A:** "Full animation films, like Toy Story."

> **Q (Team):** "What performance do you expect?"
>
> **A:** "Every frame must render within minutes, in HD at 24 FPS."

> **Q (Team):** "Do you have a precise render time target per frame?"
>
> **A:** "No fixed render time, but a 90-minute movie must be rendered in 2 months. 10 minutes per frame is too long, 1 minute is still a bit too long."

**My conclusion:** This is offline rendering, not real-time: 24 FPS is the film frame rate of the output. A 90-minute movie is 90 × 60 × 24 = 129 600 frames. Two months is about 86 400 minutes, so on a single machine the target is around 40 seconds per frame. This target scales with the number of machines rendering in parallel, which we still need to know.

### Project constraints

> **Q (Team):** "What is the deadline for the first delivery?"
>
> **A:** "15 January."

> **Q (Team):** "What budget do you have for this project?"
>
> **A:** "500 000 euros."

**My conclusion:** The budget is a quarter of one year of licences, which makes the project worth it for the client. The deadline is short (about two months), so the scope of the first version must be prioritised.

### Open questions

- **Open-source dependencies in a proprietary product:** the studio wants to own the ray tracer, so "open source" probably means using open-source libraries, not publishing the code. Which licences are acceptable? A GPL library could force the studio to publish its code, while MIT, BSD or Apache libraries would not.
- **Film rendering schedule:** the 90-minute movie must be rendered in 2 months. Do these 2 months start after the delivery on 15 January, or do they overlap with the development of the ray tracer?
- **In-house maintenance without software practices:** the client wants to maintain the ray tracer in-house, but the studio has no version control and no documentation format. Do they have C++ developers able to take over and maintain a ray tracer? Who will train them?

## State of the art

| Solution | Maker | Licence | Pricing (date checked) | Capabilities | Sources |
|---|---|---|---|---|---|
| RenderMan | Pixar | Paid | ~$595 per licence + $250/year (2026-11-16) | Used for Pixar films, works with Maya | [Pixar](https://renderman.pixar.com/store/), [FitGap](https://us.fitgap.com/products/008656/renderman) |
| Arnold | Autodesk | Paid (subscription) | ~$430/year per user (2026-11-16) | Built into Maya | [Autodesk](https://www.autodesk.com/products/arnold/subscribe), [FitGap](https://us.fitgap.com/products/008657/autodesk-arnold) |
| V-Ray | Chaos | Paid (subscription) | $540/year (2026-11-16) | Film and architecture, works with Maya | [CG Channel](https://www.cgchannel.com/2025/05/chaos-updates-v-ray-corona-and-enscape-subscription-plans/), [Renderahouse](https://www.renderahouse.com/blog/vray-pricing) |
| Cycles | Blender | Open source | Free | Built into Blender | [Blender](https://www.blender.org/features/rendering/) |
| pbrt-v4 | Pharr, Jakob, Humphreys | Open source | Free | Made for learning and research | [pbrt.org](https://pbrt.org/) |

All these tools can render a film. The paid ones are paid per machine, so with a big render farm it becomes very expensive (2 million per year for the client). The open-source ones are free, but the studio would depend on the community to fix bugs, and the client doesn't want that. None of them lets the studio own the code.

## What is ray tracing?

Ray tracing is a way to render a 3D scene by simulating how light moves. We have a scene with objects, materials, lights and a camera. For each pixel, we send a ray from the camera and look for the first object it hits. Then we compute the colour of this point: we check if a light can reach it (shadows), and we send new rays for reflections. As output, we get an image. It looks very realistic, but it takes a lot of computation. [Ray tracing explaination](https://www.youtube.com/watch?v=H5TB2l7zq6s)

**Sources:** I started from [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). The reference I would come back to is [Physically Based Rendering (pbrt)](https://pbr-book.org/).

## What is C++?

C++ is a compiled programming language. It is very fast and gives a lot of control over the memory and the hardware.

C++ is also very free. It doesn't force one way to code: in Java everything must be a class, but in C++ we can use functions, classes or both. It is not owned by a company, it is an ISO standard with several compilers (GCC, Clang, MSVC). Because of this freedom, the team has to choose its own rules.

### Programming paradigms

C++ can be procedural (functions, like C), object-oriented (classes, inheritance) and generic (templates). It also has lambdas, like in JavaScript. Compared to JavaScript or PHP, it is stricter because types are checked when we compile.

### What to watch out for

There is no garbage collector, so we have to manage the memory ourselves. If we forget to free memory, we get a memory leak. If we use memory that was already freed, the program can crash or give wrong results without any error. Smart pointers (`std::unique_ptr`, `std::shared_ptr`) help to avoid these problems.

### Shaping the domain model

Each concept of the client becomes a class: `Vector3`, `Ray`, `Camera`, `Material`, `Light`, `Scene`. All the objects a ray can hit (sphere, triangle...) can inherit from one `Shape` class with an `intersect` method. This way, we can add new shapes without changing the rest of the code.

**Sources:** I started from [learncpp.com](https://www.learncpp.com/). The references I would come back to are [cppreference.com](https://en.cppreference.com/) and the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).