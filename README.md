# AloyEngine
 
## Basic 3D engine built with GLFW and OpenGL

Features:
- ECS
- ImGui interface
- Convinient input system
- PBR Materials (albedo, normal, bump maps)
- Custom event system

Event system is inspired by Unity where each class derived from MonoBehaviour automatically "subscribes" for a number of events such as Update, OnGUI etc. This engine implemets it via singleton  (even though it's kind of evil xD). Each object derived from EventSubscribed in virtual constructor subscribes to a static EventDispatcher. Event handler has to derive from Event<T> with *subscriber type* as template parrameter i.e. Event<ImGuiEventSubscriber>. Then in *handle* method it calls appropriate event handler of that subscriber.
 
Implememting new event boils down to creating *YourEventSubscriber: public EventSubscribed*, deriving from it, and creating *YourEvent: public Event<YourEventSubscriber>*. Any time you want to fire that event call *EventDispatcher::dispatch(YourEvent())*

<hr>
 
This project is a compilation of design solution I came up with after severla educational projects
