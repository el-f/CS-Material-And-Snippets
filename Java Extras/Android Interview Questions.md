# Android Interview Questions

credit: @paulfranco

### Q1: Explain activity lifecycle ☆☆

**Answer:**
As a user navigates through, out of, and back to your app, the Activity instances in your app transition through different states in their lifecycle.

To navigate transitions between stages of the activity lifecycle, the Activity class provides a core set of six callbacks: `onCreate()`, `onStart()`, `onResume()`, `onPause()`, `onStop()`, and `onDestroy()`. The system invokes each of these callbacks as an activity enters a new state. 

<div class="text-center"/>
<img src="https://developer.android.com/guide/components/images/activity_lifecycle.png" class="img-fluid" />
</div>


**Source:** _developer.android.com_
### Q2: What is an Activity? ☆

**Answer:**
An **activity** provides the window in which the app draws its UI. This window typically fills the screen, but may be smaller than the screen and float on top of other windows. Generally, one activity implements one screen in an app. For instance, one of an app’s activities may implement a Preferences screen, while another activity implements a Select Photo screen.

**Source:** _github.com_
### Q3: Explain briefly all the Android application components ☆☆

**Answer:**
**App components** are the essential building blocks of an Android app. Each component is an entry point through which the system or a user can enter your app.

There are four different types of app components:

* **Activities** - An activity is the entry point for interacting with the user. It represents a single screen with a user interface.
* **Services** - A service is a general-purpose entry point for keeping an app running in the background for all kinds of reasons. It is a component that runs in the background to perform long-running operations or to perform work for remote processes.
* **Broadcast receivers** - A broadcast receiver is a component that enables the system to deliver events to the app outside of a regular user flow, allowing the app to respond to system-wide broadcast announcements.
* **Content providers** - A content provider manages a shared set of app data that you can store in the file system, in a SQLite database, on the web, or on any other persistent storage location that your app can access.

**Source:** _developer.android.com_
### Q4: What is 'Context' on Android? ☆☆

**Answer:**
The documentation itself provides a rather straightforward explanation: The Context class is an “Interface to global information about an application environment".

We may assume a **Context** is a handle to the system; it provides services like resolving resources, obtaining access to databases and preferences, and so on. An Android app has activities. Context is like a handle to the environment your application is currently running in. The activity object inherits the Context object.

**Source:** _stackoverflow.com_
### Q5: What types of Context do you know? ☆☆

**Answer:**
The are mainly two types of context:

* **Application Context**: It is an instance that is the singleton and can be accessed in activity via `getApplicationContext()`. This context is tied to the lifecycle of an application. The application context can be used where you need a context whose lifecycle is separate from the current context or when you are passing a context beyond the scope of activity.

* **Activity Contex**t: This context is tied to the lifecycle of an activity. The activity context should be used when you are passing the context in the scope of an activity or you need the context whose lifecycle is attached to the current context.

**Source:** _blog.mindorks.com_
### Q6: How do I pass data between Activities in Android application? ☆☆

**Details:**
I have a scenario where, after logging in through a login page, there will be a sign-out button on each activity. Can you guide me on how to keep session id available to all activities?

**Answer:**
The easiest way to do this would be to pass the session id to the signout activity in the **Intent** you're using to start the activity:

```java
Intent intent = new Intent(getBaseContext(), SignoutActivity.class);
intent.putExtra("EXTRA_SESSION_ID", sessionId);
startActivity(intent);
```
Access that intent on next activity:
```java
String sessionId = getIntent().getStringExtra("EXTRA_SESSION_ID");
```

**Source:** _stackoverflow.com_
### Q7: How can I get the context in a fragment? ☆☆

**Answer:**
You can use `getActivity()`, which returns the activity associated with a fragment. The activity is a context (since Activity extends `Context`).

You can also override the `onAttach` method of fragment:

```java
public static class DummySectionFragment extends Fragment{
...
    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        DBHelper = new DatabaseHelper(activity);
    }
}
```

**Source:** _stackoverflow.com_
### Q8: Is it possible to implement the model–view–controller pattern in Java for Android? ☆☆

**Answer:**
In Android you **don't have MVC**, but you have the following:

* You define your user interface in  various XML files by resolution, hardware, etc.
* You define your resources in various XML files by locale, etc.
* You extend clases like ListActivity, TabActivity and make use of the XML file by inflaters.
* You can create as many classes as you wish for your business logic.
* A lot of Utils have been already written for you - DatabaseUtils, Html.

**Source:** _stackoverflow.com_
### Q9: What is an Intent in Android? ☆☆

**Answer:**
An Intent is basically a message that is passed between components (such as Activities, Services, Broadcast Receivers, and Content Providers).So, it is almost equivalent to parameters passed to API calls. The fundamental differences between API calls and invoking components via intents are:

* API calls are synchronous while intent-based invocations are asynchronous.
* API calls are compile-time binding while intent-based calls are run-time binding.

To listen for an broadcast intent (like the phone ringing, or an SMS is received), you implement a **broadcast receiver**, which will be passed the intent. To declare that you can handle another's app intent like "take picture", you declare an intent filter in your app's manifest file.

If you want to fire off an intent to do something, like pop up the dialer, you fire off an intent saying you will.

An Intent provides a facility for performing late runtime binding between the code in different applications. 

**Source:** _stackoverflow.com_
### Q10: What is the most appropriate way to store user settings in Android application? ☆☆

**Answer:**
In general **SharedPreferences** are your best bet for storing preferences, so in general I'd recommend that approach for saving application and user settings.

The only area of concern here is what you're saving. Passwords are always a tricky thing to store, and I'd be particularly wary of storing them as clear text. The Android architecture is such that your application's SharedPreferences are sandboxed to prevent other applications from being able to access the values so there's some security there, but physical access to a phone could potentially allow access to the values.

**Source:** _stackoverflow.com_
### Q11: In what situation should one use RecyclerView over ListView? ☆☆

**Answer:**
**RecyclerView** was created as a **ListView** improvement, so yes, you can create an attached list with **ListView** control, but using **RecyclerView** is easier as it:

* Reuses cells while scrolling up/down - this is possible with implementing View Holder in the ListView adapter, but it was an optional thing, while in the RecycleView it's the default way of writing adapter.
* Decouples list from its container - so you can put list items easily at run time in the different containers (linearLayout, gridLayout) with setting LayoutManager.

To conclude, **RecyclerView** is a more flexible control for handling "list data" that follows patterns of delegation of concerns and leaves for itself only one task - recycling items.

**Source:** _stackoverflow.com_
### Q12: Tell about Constraint Layout ☆☆

**Answer:**
**ConstraintLayout** allows you to create large and complex layouts with a flat view hierarchy (no nested view groups). It's similar to **RelativeLayout** in that all views are laid out according to relationships between sibling views and the parent layout, but it's more flexible than RelativeLayout and easier to use with Android Studio's Layout Editor.

Intention of ConstraintLayout is to optimize and flatten the view hierarchy of your layouts by applying some rules to each view to avoid nesting.

**Source:** _developer.android.com_
### Q13: What is Dalvik? ☆☆

**Answer:**
**Dalvik** is a Just In Time (JIT) compiler. By the term JIT, we mean to say that whenever you run your app in your mobile device then that part of your code that is needed for execution of your app will only be compiled at that moment and rest of the code will be compiled in the future when needed. The JIT or Just In Time compiles only a part of your code and it has a smaller memory footprint and due to this, it uses very less physical space on your device.

**Source:** _blog.mindorks.com_
### Q14: What is a difference between Spannable and String? ☆

**Answer:**
A **Spannable** allows to attach formatting information like bold, italic, ... to sub-sequences ("spans", thus the name) of the characters. It can be used whenever you want to represent "rich text".

**Source:** _stackoverflow.com_
### Q15: How does the OutOfMemory happens? ☆☆

**Answer:**
**Out of memory** error is very common error when you are developing for a application that deals with multiple images sets or large bitmaps or some Animation stuff. In Android, every application runs in a Linux Process. Each Linux Process has a Virtual Machine (Dalvik Virtual Machine) running inside it. There is a limit on the memory a process can demand and it is different for different devices and also differs for phones and tablets. When some process demands a higher memory than its limit it causes a error i.e **Out of memory** error.

There are number of reasons why we get a Out of memory errors. Some of those are:

1. You are doing some operation that continuously demands a lot of memory and at some point it goes beyond the max heap memory limit of a process.

2. You are leaking some memory i.e you didn’t make the previous objects you allocated eligible for Garbage Collection (GC). This is called Memory leak.

3. You are dealing with large bitmaps and loading all of them at run time. You have to deal very carefully with large bitmaps by loading the size that you need not the whole bitmap at once and then do scaling.

**Source:** _blogs.innovationm.com_
### Q16: How to persist data in an Android app? ☆☆

**Answer:**
There are basically four different ways to store data in an Android app:

1. Shared Preferences - to save primitive data in key-value pairs
2. Internal Storage - you need to store data to the device filesystem, but you do not want any other app (even the user) to read this data
3. External Storage -  you might want the user to view the files and data saved by your app
4. SQLite database


**Source:** _www.androidauthority.com_
### Q17: Explain Android notification system ☆☆

**Answer:**
A **notification** is a message that Android displays outside your app's UI to provide the user with reminders, communication from other people, or other timely information from your app. Users can tap the notification to open your app or take an action directly from the notification.

Notifications appear to users in different locations and formats, such as an icon in the status bar, a more detailed entry in the notification drawer, as a badge on the app's icon, and on paired wearables automatically. Beginning with Android 5.0, notifications can appear on the lock screen.

Starting in Android 8.0 (API level 26), all notifications must be assigned to a channel or it will not appear. By categorizing notifications into channels, users can disable specific notification channels for your app (instead of disabling all your notifications), and users can control the visual and auditory options for each channel—all from the Android system settings.

**Source:** _developer.android.com_
### Q18: Why is it recommended to use only the default constructor to create a Fragment? ☆☆

**Answer:**
In short, Fragments need to have a no-args constructor for the Android system to instantiate them. Your Fragment subclasses need a public empty constructor as this is what's being called by the framework.

It is used in the case when device has to restore the state of a fragment. No data will be passed and a default fragment will be created and then the state will be restored. Since the system has no way to know what you passed in your constructor or your `newInstance`, default constructor will be used and saved bundle should be passed via onCreate after the fragment is actually instantiated with the default constructor.

**Source:** _www.quora.com_
### Q19: What is the difference between Bitmap and Drawable in Android? ☆

**Answer:**
* A **Bitmap** is a representation of a bitmap image (something like java.awt.Image).
* A **Drawable** is an abstraction of "something that can be drawn". It could be a Bitmap (wrapped up as a BitmapDrawable), but it could also be a solid color, a collection of other Drawable objects, or any number of other structures.

**Source:** _stackoverflow.com_
### Q20: Mention the difference between RelativeLayout and LinearLayout? ☆

**Answer:**
* **Linear Layout** — Arranges elements either vertically or horizontally. i.e. in a row or column.
* **Relative Layout** — Arranges elements relative to parent or other elements.

**Source:** _android.jlelse.eu_

### Q21: What is the actual differences between a activity context and application context? ☆☆☆

**Answer:**
They are both instances of `Context`, but the application instance is tied to the lifecycle of the application, while the Activity instance is tied to the lifecycle of an Activity. Thus, they have access to different information about the application environment.

If you read the docs at `getApplicationContext` it notes that you should only use this if you need a context whose lifecycle is separate from the current context.

In general, use the activity context unless you have a good reason not to.

**Source:** _stackoverflow.com_
### Q22: What is the difference between Activity and Context? ☆☆☆

**Answer:**
`Context` is the Base Object. So every `Activity` same as `Application` derives from `Context`. This means that every `Activity` and `every` Application IS a `Context`.

An Application context lasts, as long as your app is alive, while the Activity context dies with your Activity (it is not valid after `onDestroy` of that Activity).

So if you need the Context across Activities (i.e. in a Singleton) you will be better off using an Application context.

**Source:** _stackoverflow.com_
### Q23: How could you pass data between activities without Intent? ☆☆☆

**Answer:**
The **Application** object is a way to go, and it is sometimes easier when dealing with the same state across multiple activities (as opposed to having to get/put it everywhere), or objects more complex than _primitives_ and _Strings_.

You can extend Application, and then set/get whatever you want there and access it from any Activity (in the same application) with `getApplication()`.

Also keep in mind that other approaches you might see, like _statics_, can be problematic because they can lead to memory leaks. Application helps solve this too.

**Source:** _stackoverflow.com_
### Q24: When to use Fragments vs Activities? ☆☆☆

**Answer:**
**Activities** are designed to represent a single screen of my application, while **Fragments** are designed to be reusable UI layouts with logic embedded inside of them.

Google advises you to always use Fragments. In the simplest case, Fragments are used like containers of activities.Android 4 (ICS) supports both Smartphones and Tablets. This means the same application will be running on a smartphone and a tablet and they are likely to be very different.

Historically each screen in an Android app was implemented as a separate Activity. This creates a challenge in passing information between screens because the Android Intent mechanism does not allow passing a reference type (i.e. object) directly between Activities. By making each screen a separate Fragment, this data passing headache is completely avoided. Fragments always exist within the context of a given Activity and can always access that Activity. By storing the information of interest within the Activity, the Fragment for each screen can simply access the object reference through the Activity.

**Source:** _stackoverflow.com_
### Q25: Explain key differences between Service and IntentService ☆☆☆

**Answer:**
**When to use?**

 - The *Service* can be used in tasks with no UI, but shouldn't be too long.  If you need to perform long tasks, you must use threads within Service.

 - The *IntentService* can be used in long tasks usually with no communication to Main Thread.  If communication is required, can use Main Thread handler or broadcast intents. Another case of use is when callbacks are needed (Intent triggered tasks).

**How to trigger?**

 - The *Service* is triggered by calling method `startService()`.

 - The *IntentService* is triggered using an Intent, it spawns a new worker thread and the method `onHandleIntent()` is called on this thread.

**Triggered From**

 - The *Service* and *IntentService* may be triggered from any thread, activity or other application component.

**Runs On**

 - The *Service* runs in background but it runs on the Main Thread of the application. 

 - The *IntentService* runs on a separate worker thread.

**Limitations / Drawbacks**

 - The *Service* may block the Main Thread of the application.

 - The *IntentService* cannot run tasks in parallel. Hence all the consecutive intents will go into the message queue for the worker thread and will execute sequentially.

**When to stop?**

 -  If you implement a *Service*, it is your responsibility to stop the service when its work is done, by calling `stopSelf()` or `stopService()`. (If you only want to provide binding, you don't need to implement this method).

 - The *IntentService* stops the service after all start requests have been handled, so you never have to call `stopSelf()`.

**Source:** _stackoverflow.com_
### Q26: How to declare global variables in Android? ☆☆☆

**Answer:**
The way to do this is to create your own subclass of `android.app.Application`, and then specify that class in the application tag in your manifest.

```java
public class MyApp extends Application {
  String foo;
}
```
In the AndroidManifest.xml add android:name
```xml
<application android:name=".MyApp" 
       android:icon="@drawable/icon" 
       android:label="@string/app_name">
```

**Source:** _stackoverflow.com_
### Q27: What is an Android PendingIntent? ☆☆☆

**Answer:**
**Intents** are the standard messaging mechanism in Android that expresses the user’s intention to perform some work. 

A **PendingIntent** specifies an action to take in the future. It lets you pass a future Intent to another application and allow that application to execute that Intent _as if it had the same permissions as your application_.

By giving a PendingIntent to another application, you are granting it the right to perform the operation you have specified as if the other application was yourself (with the same permissions and identity). 

**Source:** _stackoverflow.com_
### Q28: What is the difference between compileSdkVersion and targetSdkVersion? ☆☆☆

**Answer:**
* The `compileSdkVersion` is the version of the API the app is compiled against. This means you can use Android API features included in that version of the API (as well as all previous versions, obviously). If you try and use API 16 features but set `compileSdkVersion` to 15, you will get a compilation error. If you set `compileSdkVersion` to 16 you can still run the app on a API 15 device as long as your app's execution paths do not attempt to invoke any APIs specific to API 16.

* The `targetSdkVersion` has nothing to do with how your app is compiled or what APIs you can utilize. The `targetSdkVersion` is supposed to indicate that you have tested your app on (presumably up to and including) the version you specify. This is more like a certification or sign off you are giving the Android OS as a hint to how it should handle your app in terms of OS features.

**Source:** _stackoverflow.com_
### Q29: Why fragments, and when to use fragments instead of activities? ☆☆☆

**Answer:**
In short, fragments live inside activities, and each activity can host many fragments. Like activities, they have a specific lifecycle, unlike activities, they are not top-level application components. 

* Advantages of fragments include code reuse and modularity (e.g., using the same list view in many activities), including the ability to build multi-pane interfaces (mostly useful on tablets). A fragment can be used in multiple activities. By making each screen a separate Fragment, this data passing headache is completely avoided. Fragments always exist within the context of a given Activity and can always access that Activity. By storing the information of interest within the Activity, the Fragment for each screen can simply access the object reference through the Activity.

* The main disadvantage is (some) added complexity. You can generally achieve the same thing with (custom) views in a non-standard and less robust way.

**Source:** _stackoverflow.com_
### Q30: What is the difference between invisible and gone for the View visibility status? ☆☆☆

**Answer:**
* **Invisible** - this view is invisible, but it still takes up space for layout purposes.

* **Gone** - this view is invisible, and it doesn't take any space for layout purposes.

Looks like analogous to `display:none` & `visibility:hidden` in HTML/CSS.

**Source:** _stackoverflow.com_
### Q31: What is the difference between AsyncTask and Thread/Runnable? ☆☆☆

**Answer:**
* **AsyncTask** is a convenience class for doing some work on a new thread and use the results on the thread from which it got called (usually the UI thread) when finished. It's just a wrapper which uses a couple of runnables but handles all the intricacies of creating the thread and handling messaging between the threads. AsyncTask is designed to be a helper class around Thread and Handler and does not constitute a generic threading framework.

* The **Runnable** interface is at the core of Java threading. The Runnable interface should be implemented by any class whose instances are intended to be executed by a thread.


**Source:** _stackoverflow.com_
### Q32: What is Parcelable in Android? ☆☆☆

**Answer:**
A **Parcelable** is the Android implementation of the Java Serializable. It assumes a certain structure and way of processing it. This way a Parcelable can be processed relatively fast, compared to the standard Java serialization. To allow your custom object to be parsed to another component they need to implement the `android.os.Parcelable` interface.

You can use Parcelable in Activity like:
```java
intent.putExtra("student", new Student("1")); //size which you are storing
```
And to get this object :
```java
Bundle data = getIntent().getExtras();
Student student = (Student) data.getParcelable("student");
```

In short use **Parcelable** to convert an object into a sequence of bytes which can be read/transferred between Activities.

**Source:** _stackoverflow.com_
### Q33: What is an AsyncTask? ☆☆

**Answer:**
`AsyncTask` is one of the easiest ways to implement parallelism in Android without having to deal with more complex methods like Threads. Though it offers a basic level of parallelism with the UI thread, it should not be used for longer operations (of, say, not more than 2 seconds). 

AsyncTask has four methods 

- `onPreExecute()` 
- `doInBackground()`
- `onProgressUpdate()`
- `onPostExecute()`

where `doInBackground()` is the most important as it is where background computations are performed.

**Source:** _stackoverflow.com_
### Q34: What is a ContentProvider and what is it typically used for? ☆☆

**Answer:**
A **content provider** manages access to a central repository of data. A provider is part of an Android application, which often provides its own UI for working with the data. However, content providers are primarily intended to be used by other applications, which access the provider using a provider client object.

Typically you work with content providers in one of two scenarios; 
* you may want to implement code to access an existing content provider in another application, or 
* you may want to create a new content provider in your application to share data with other applications.

**Source:** _developer.android.com_
### Q35: What is ADB and what is it used for? ☆☆

**Answer:**
**ADB** is the acronym for Android Debug Bridge, which is part of the Android SDK (Software Development Kit). It uses a client-server-model (i.e. adbd, the ADB daemon, is running on the device and can be connected to), and in most cases is used via an USB connection. It is also possible to use it via WiFi (wireless adb).

There's nothing you need to install on your Android device, as the ADB daemon (adbd) is already integrated into the Android OS. It is usually accessed via a command line interface from the PC, where either the full Android SDK is installed (several 30 MB download archive currently), or a massively stripped-down version for "non-developers", sometimes referred to as "Mini ADB" or "ADB essentials" (for Linux, this is only the adb executable; for Windows it's adb.exe plus two or three .dll files).

**Source:** _developer.android.com_
### Q36: What is the Dalvik Virtual Machine? ☆☆

**Answer:**
The **Dalvik Virtual Machine (DVM)** is an android virtual machine optimized for mobile devices. It optimizes the virtual machine for memory, battery life and performance.

The Dex compiler converts the class files into the `.dex` file that run on the Dalvik VM. Multiple class files are converted into one dex file.

**Source:** _www.javatpoint.com_
### Q37: What is Armv7? ☆☆

**Answer:**
There are 3 CPU architectures in Android:

* **_ARMv7_**  is the most common as it is optimised for battery consumption.
*  **_ARM64_**  is an evolved version of that that supports 64-bit processing for more powerful computing.
*  **_ARMx86_**, is the least used for these three, since it is not battery friendly. It is more powerful than the other two.

**Source:** _android.jlelse.eu_
### Q38: Explain the build process in Android ☆☆

**Answer:**
1.  First step involves compiling the resources folder (/res) using the aapt (android asset packaging tool) tool. These are compiled to a single class file called R.java. This is a class that just contains constants.
2.  Second step involves the java source code being compiled to .class files by javac, and then the class files are converted to Dalvik bytecode by the “dx” tool, which is included in the sdk ‘tools’. The output is classes.dex.
3.  The final step involves the android apkbuilder which takes all the input and builds the apk (android packaging key) file.

**Source:** _android.jlelse.eu_
### Q39: What’s the difference between onCreate() and onStart()? ☆☆

**Answer:**
*   The `onCreate()` method is called once during the Activity lifecycle, either when the application starts, or when the Activity has been destroyed and then recreated, for example during a configuration change.
*   The `onStart()` method is called whenever the Activity becomes visible to the user, typically after `onCreate()` or `onRestart()`.

**Source:** _android.jlelse.eu_
### Q40: What is View Group? How are they different from Views? ☆☆

**Answer:**
**View:** View objects are the basic building blocks of User Interface(UI) elements in Android. View is a simple rectangle box which responds to the user’s actions. Examples are EditText, Button, CheckBox etc. View refers to the `android.view.View` class, which is the base class of all UI classes.

**ViewGroup:** ViewGroup is the invisible container. It holds View and ViewGroup. For example, LinearLayout is the ViewGroup that contains Button(View), and other Layouts also. ViewGroup is the base class for Layouts.

**Source:** _android.jlelse.eu_


### Q41: What is the difference between Handler vs AsyncTask vs Thread? ☆☆☆

**Answer:**
* The **Handler** class can be used to register to a thread and provides a simple channel to send data to this thread. A Handler allows you communicate back with the UI thread from other background thread. 

* The **AsyncTask** class encapsulates the creation of a background process and the synchronization with the main thread. It also supports reporting progress of the running tasks.

* And a **Thread** is basically the core element of multithreading which a developer can use with the following disadvantage:
 * Handle synchronization with the main thread if you post back results to the user interface
 * No default for canceling the thread
 * No default thread pooling
 * No default for handling configuration changes in Android

**Source:** _stackoverflow.com_
### Q42: What is Handler and what is it used for? ☆☆☆

**Answer:**
When we install an application in Android, then it creates a thread for that application called MAIN UI Thread. All activities run inside that thread. By the android single thread model rule, we can not access UI elements (bitmap , textview etc..) directly for another thread defined inside that activity.

A **Handler** allows you communicate back with the UI thread from other background thread. This is useful in android as android doesn’t allow other threads to communicate directly with UI thread. Handler can send and process **Message** and **Runnable** objects associated with a thread’s **MessageQueue**. Each Handler instance is associated with a single thread and that thread’s message queue. When a new Handler is created, it is bound to the thread/message queue of the thread that is creating it.  To use a handler you have to subclass it and override `handleMessage()` to process messages.

There are two main uses for a Handler:
* To schedule messages and runnables to be executed as some point in the future;
* To enqueue an action to be performed on a different thread than your own.

**Source:** _stackoverflow.com_
### Q43: What is Explicit Intent? ☆☆☆

**Answer:**
**Explicit Intents** used to call a specific component. When you know which component you want to launch and you do not want to give the user free control over which component to use. For example, you have an application that has 2 activities. Activity A and activity B. You want to launch activity B from activity A. In this case you define an explicit intent targeting activity B and then use it to directly call it.

**Source:** _stackoverflow.com_
### Q44: What is Implicit Intent? ☆☆☆

**Answer:**
**Implicit Intents** used when you have an idea of what you want to do, but you do not know which component should be launched. Or if you want to give the user an option to choose between a list of components to use. 

If these Intents are send to the Android system it searches for all components which are registered for the specific action and the data type. If only one component is found, Android starts the component directly. 

For example, you have an application that uses the camera to take photos. One of the features of your application is that you give the user the possibility to send the photos he has taken. You do not know what kind of application the user has that can send photos, and you also want to give the user an option to choose which external application to use if he has more than one. In this case you would not use an explicit intent. Instead you should use an implicit intent that has its action set to ACTION_SEND and its data extra set to the URI of the photo.

**Source:** _stackoverflow.com_
### Q45: What is Intent Filter? ☆☆☆

**Answer:**
If an Intents is send to the Android system, it will determine suitable applications for this Intents. If several components have been registered for this type of Intents, Android offers the user the choice to open one of them.

This determination is based on **IntentFilters**. An IntentFilters specifies the types of Intent that an activity, service, orBroadcast Receiver can respond to. An Intent Filter declares the capabilities of a component. It specifies what anactivity or service can do and what types of broadcasts a Receiver can handle. It allows the corresponding component to receive Intents of the declared type. IntentFilters are typically defined via the AndroidManifest.xml file. For BroadcastReceiver it is also possible to define them in coding. An IntentFilters is defined by its category, action and data filters. It can also contain additional metadata.

If a component does not define an Intent filter, it can only be called by explicit Intents.

**Source:** _stackoverflow.com_
### Q46: What does LayoutInflater in Android do? ☆☆☆

**Answer:**
The **LayoutInflater** class is used to instantiate the contents of layout XML files into their corresponding View objects.

In other words, it takes an XML file as input and builds the View objects from it.

**Source:** _stackoverflow.com_
### Q47: Android Log.v(), Log.d(), Log.i(), Log.w(), Log.e(). When to use each one? ☆☆☆

**Answer:**
Let's go in reverse order:

 - [**Log.e**](https://developer.android.com/reference/android/util/Log.html#e(java.lang.String,java.lang.String)): This is for when bad stuff happens. Use this tag in places like inside a catch statement. You *know* that an *error* has occurred and therefore you're logging an error.

 - [**Log.w**](https://developer.android.com/reference/android/util/Log.html#w(java.lang.String,java.lang.String)): Use this when you suspect something shady is going on. You may not be completely in full on error mode, but maybe you recovered from some unexpected behavior. Basically, use this to log stuff you didn't expect to happen but isn't necessarily an error. Kind of like a "hey, this happened, and it's *weird*, we should look into it."

 - [**Log.i**](https://developer.android.com/reference/android/util/Log.html#i(java.lang.String,java.lang.String)): Use this to post useful *information* to the log. For example: that you have successfully connected to a server. Basically use it to report successes.

 - [**Log.d**](https://developer.android.com/reference/android/util/Log.html#d(java.lang.String,java.lang.String)): Use this for *debugging* purposes. If you want to print out a bunch of messages so you can log the exact flow of your program, use this. If you want to keep a log of variable values, use this.

 - [**Log.v**](https://developer.android.com/reference/android/util/Log.html#v(java.lang.String,java.lang.String)): Use this when you want to go absolutely nuts with your logging. If for some reason you've decided to log every little thing in a particular part of your app, use the Log.v tag.

And as a bonus...

 - [**Log.wtf**](https://developer.android.com/reference/android/util/Log.html#wtf(java.lang.String,java.lang.String)): Use this when stuff goes absolutely, horribly, holy-crap wrong. You know those catch blocks where you're catching errors that you *never* should get...yeah, if you wanna log them use Log.wtf

**Source:** _stackoverflow.com_
### Q48: What are the differences between onCreate(), onCreateView(), and onActivityCreated() in fragments and what would they each be used for? ☆☆☆

**Answer:**
They are all called in the Fragment but are called at different times.
The `onCreate()` is called first, for doing any non-graphical initialisations. Next, you can assign and declare any View variables you want to use in `onCreateView()`. Afterwards, use `onActivityCreated()` to do any final initialisations you want to do once everything has completed.

Also check this two diagrams:

<div class="text-center"/>
<img src="https://i.stack.imgur.com/tICd7.png" class="img-fluid" />
</div>

And, 

<div class="text-center"/>
<img src="https://i.stack.imgur.com/qyU1H.png" class="img-fluid" />
</div>



**Source:** _stackoverflow.com_
### Q49: What is the difference between onCreate() and onCreateView() lifecycle methods in Fragment? ☆☆☆

**Answer:**
* **onCreate** is called on initial creation of the fragment. You do your non graphical initializations here. It finishes even before the layout is inflated and the fragment is visible.

* **onCreateView** is called to inflate the layout of the fragment i.e graphical initialization usually takes place here. It is always called sometimes after the onCreate method.

**Source:** _stackoverflow.com_
### Q50: When to use Android's ArrayMap instead of a HashMap? ☆☆☆

**Answer:**
**ArrayMap** uses way less memory than **HashMap** and is recommended for up to a few hundred items, especially if the map is not updated frequently. Spending less time allocating and freeing memory may also provide some general performance gains.

Update performance is a bit worse because any insert requires an array copy. Read performance is comparable for a small number of items and uses binary search.

**Source:** _stackoverflow.com_
### Q51: What are the differences between ArrayList and ArrayMap? ☆☆☆

**Answer:**
**ArrayMap** keeps its mappings in an array data structure — an integer array of hash codes for each item, and an Object array of the key -> value pairs.

Where **ArrayList** is a List. Resizable-array implementation of the List interface. Implements all optional list operations, and permits all elements, including null.

**Source:** _stackoverflow.com_
### Q52: Explain how HashMap works ☆☆☆

**Answer:**
HashMap is basically an Array of HashMap.Entry objects (Entry is an inner class of HashMap).

What happens when a key/value is inserted in HashMap ?

*   HashCode of the key is calculated, and that value is assigned to the hashCode variable of EntryClass.
*   Then, using hashCode we get the index of the bucket where it will be stored.
*   If the bucket is having a pre-existing element, the new element is inserted with the last element pointing to new one — essentially making the bucket a LinkedList.

Now, when you query it to get the value for a key, it comes in O(1). But most important thing is that it comes at the cost of more space(memory).

**Source:** _medium.com_
### Q53: What are Android Annotations and what are they used for? ☆☆☆

**Answer:**
**Android Annotations** is an annotation-driven framework that allows you to simplify the code in your applications and reduces the boilerplate of common patterns, such as setting click listeners, enforcing ui/background thread executions, etc.

I don't recommend using it; it's buggy, and unstable. In my current job I am working on a project and my task is to remove Android Annotations. I would suggest using Dagger 2, Butterknife, and RxJava.

**Source:** _stackoverflow.com_
### Q54: What is ART? ☆☆☆

**Answer:**
**ART** or Android Runtime is an Android runtime that uses Ahead Of Time (AOT). By using AOT, what is does is it converts or compiles the whole High-level language code into Machine level code and at the time of installation of the app and not dynamically as the application runs (like in case of Dalvik). By compiling the whole code during installation results in no lag that we see when we run our app on our device.

**Source:** _blog.mindorks.com_
### Q55: What is RenderScript and when should we (really) use it? ☆☆☆

**Answer:**
**RenderScript** is a framework for running computationally intensive tasks at high performance on Android. RenderScript is primarily oriented for use with data-parallel computation, although serial workloads can benefit as well. The RenderScript runtime parallelizes work across processors available on a device, such as multi-core CPUs and GPUs. This allows you to focus on expressing algorithms rather than scheduling work. RenderScript is especially useful for applications performing image processing, computational photography, or computer vision.

If your application is doing a lot of cpu based data processing (i.e. in Dalvik or the NDK), and you would like a speedup, you should look at RS.

**Source:** _developer.android.com_
### Q56: Explain String vs StringBuilder vs SpannedString vs SpannableString vs SpannableStringBuilder vs CharSequence  ☆☆☆

**Answer:**
* A `String` is immutable (ie, the text can't change). It also doesn't have any spans associated with it. (Spans are ranges over the text that include styling information like color, highlighting, italics, links, etc.) So you can use a `String` when your text doesn't need to be changed and doesn't need any styling.

* A `StringBuilder` has mutable text, so you can modify it without creating a new object. However, it doesn't have any span information. It is just plain text. So use a `StringBuilder` when you need to change the text, but you don't care about styling it.

* A `SpannedString` has immutable text (like a `String`) and immutable span information. It is a concrete implementation of the requirements defined by the `Spanned` interface. Use a `SpannedString` when your text has style but you don't need to change either the text or the style after it is created.

*Note:* There is no such thing as a `SpannedStringBuilder` because if the text changed then the span information would also very likely have to change.

* A `SpannableString` has immutable text, but its span information is mutable. It is a concrete implementation of the requirements defined by the `Spannable` interface. Use a `SpannableString` when your text doesn't need to be changed but the styling does.

* A `SpannableStringBuilder` has both mutable text and span information. It is a concrete implementation of the requirements defined by the `Spannable` and `Editable` interfaces (among others). Use a `SpannableStringBuilder` when you will need to update the text and its style.

* A `CharSequence` is an interface and not a concrete class. That means it just defines a list of rules to follow for any class that implements it. And all of the classes mentioned above implement it. So you can use a `CharSequence` when you want to generalize the type of object that you have for maximum flexibility. You can always downcast it to a `String` or `SpannableStringBuilder` or whatever later if you need to.

**Source:** _stackoverflow.com_
### Q57: What is the best way to update the screen periodically? ☆☆☆

**Answer:**
Use **Handler**. _Timer_ on the other hand will execute on another thread so it cannot update the views.

```java
Handler handler = new Handler();
Runnable runnable = new Runnable() {
     public void run() {
         doStuff();
     }
};
```

**Source:** _stackoverflow.com_
### Q58: What is the ViewHolder pattern? Why should we use it? ☆☆☆

**Answer:**
Every time when the adapter calls `getView()` method, the `findViewById()` method is also called. This is a very intensive work for the mobile CPU and so affects the performance of the application and the battery consumption increases.  **ViewHolder** is a design pattern which can be applied as a way around repeated use of `findViewById()`.

A ViewHolder holds the reference to the id of the view resource and calls to the resource will not be required after you "find" them: Thus performance of the application increases.

```java
private static class ViewHolder {
  final TextView text;
  final TextView timestamp;
  final ImageView icon;
  final ProgressBar progress;

  ViewHolder(TextView text, TextView timestamp, ImageView icon, ProgressBar progress) {
    this.text = text;
    this.timestamp = timestamp;
    this.icon = icon;
    this.progress = progress;
  }
}

public View getView(int position, View convertView, ViewGroup parent) {
  View view = convertView;
  if (view == null) {
    view = // inflate new view
    ViewHolder holder = createViewHolderFrom(view);
    view.setTag(holder);  
  }
  ViewHolder holder = view.getTag();
  // TODO: set correct data for this list item
  // holder.icon.setImageDrawable(...)
  // holder.text.setText(...)
  // holder.timestamp.setText(...)
  // holder.progress.setProgress(...)
  return view;
}

private ViewHolder createViewHolderFrom(View view) {
    ImageView icon = (ImageView) view.findViewById(R.id.listitem_image);
    TextView text = (TextView) view.findViewById(R.id.listitem_text);
    TextView timestamp = (TextView) view.findViewById(R.id.listitem_timestamp);
    ProgressBar progress = (ProgressBar) view.findViewById(R.id.progress_spinner);

    return new ViewHolder(text, timestamp, icon, progress);
}
```

`View.setTag(Object)` allows you to tell the View to hold an arbitrary object. If we use it to hold an instance of our ViewHolder after we do our findViewById(int) calls, then we can use `View.getTag()` on recycled views to avoid having to make the calls again and again.

**Source:** _stackoverflow.com_
### Q59: What is the difference between ListView and RecyclerView? ☆☆☆

**Answer:**
For list views to have good performance you'll need to implement the **View Holder** pattern, and that's easy to mess up especially when you want to populate the list with several different kinds of views.

The **RecyclerView** bakes this pattern in, making it more difficult to mess up. It's also more flexible, making it easier to handle different layouts, that aren't straight linear, like a grid.

**Source:** _stackoverflow.com_
### Q60: What is the difference between Adapter and Loader in Android? ☆☆☆

**Answer:**
An **Adapter** object acts as a bridge between an AdapterView and the underlying data for that view. The Adapter provides access to the data items. 

**Loaders** make it easy to asynchronously load data in an Activity or Fragment.

Both provide an abstraction for data access, but the **Loader** performs the query in the background whereas an **Adapter** executes in the current (presumably UI) thread.

**Source:** _stackoverflow.com_

### Q61: How to avoid reverse engineering of an APK file? ☆☆☆☆

**Answer:**
AFAIK, there is not any trick for complete avoidance of reverse engineering. However, there are steps you can take to protect your source code, or at least what it does if not everything:
1. Use tools like ProGuard. These will obfuscate your code.
2. Move the most critical parts of the service out of the app, and into a webservice, hidden behind a server side.
3. When storing values on the device, don't store them in a raw format. 
4. Use SSL and properly validate the server certificate. 
5. Insert random useless source code into your app, so that the hacker is looking for a needle in a haystack.

**Source:** _stackoverflow.com_
### Q62: Discuss Singletons vs. Application Context for app-global state ☆☆☆☆

**Answer:**
According Android documentation there is normally no need to subclass Application. In most situation, static singletons can provide the same functionality in a more modular way. If your singleton needs a global context (for example to register broadcast receivers), the function to retrieve it can be given a Context which internally uses Context.getApplicationContext() when first constructing the singleton.

On the other hand singletons are a nightmare for testing and, if lazily initialized, will introduce "state indeterminism" with subtle side effects. Visibility has been mentioned as another problem, and since singletons imply "global" (= random) access to shared state, subtle bugs may arise when not properly synchronized in concurrent applications.

Although the app context can be considered a singleton itself, it is framework-managed and has a well defined life-cycle, scope, and access path. Hence I believe that if you do need to manage app-global state, it should go here, nowhere else.

**Source:** _stackoverflow.com_
### Q63: What is the difference between getContext() , getApplicationContext() , getBaseContext() , and "this"? ☆☆☆☆

**Answer:**
- `View.getContext()`:  Returns the context the view is currently running in.  Usually the currently active Activity.

- `Activity.getApplicationContext()`:  Returns the context for the entire application (the process all the Activities are running inside
   of).  Use this instead of the current Activity context if you need a
   context tied to the lifecycle of the entire application, not just the
   current Activity.

- `ContextWrapper.getBaseContext()`:  If you need access to a Context from within another context, you use a ContextWrapper.  The
   Context referred to from inside that ContextWrapper is accessed via
   getBaseContext().

- `this` is refer current class object always. `this` and `getContext() `are not always same e.g. in Activity class, you can use `this` because `Activity` inherits from `Context` but method `getContext()` is not in `Activity` class.

**Source:** _stackoverflow.com_
### Q64: When to use Android Loaders? ☆☆☆

**Answer:**
**Loaders** are best option when we want to observe a data source and change our view so it will display the new data if your data source is _constantly updating_. For example, like a stock-ticker app. If your data isn't constantly updating, then don't use a loader. For example, if your data source is only retrieved once, then there's no need for a Loader.

**Source:** _stackoverflow.com_
### Q65: How would you communicate between two Fragments? ☆☆☆

**Answer:**
All Fragment-to-Fragment communication is done either through a shared **ViewModel** or through the associated **Activity**. Two Fragments should never communicate directly.

The recommended way to communicate between fragments is to create a shared **ViewModel** object. Both fragments can access the ViewModel through their containing Activity. The Fragments can update data within the ViewModel and if the data is exposed using LiveData the new state will be pushed to the other fragment as long as it is observing the LiveData from the ViewModel.

```java
public class SharedViewModel extends ViewModel {
 private final MutableLiveData < Item > selected = new MutableLiveData < Item > ();

 public void select(Item item) {
  selected.setValue(item);
 }

 public LiveData < Item > getSelected() {
  return selected;
 }
}


public class MasterFragment extends Fragment {
 private SharedViewModel model;
 public void onCreate(Bundle savedInstanceState) {
  super.onCreate(savedInstanceState);
  model = ViewModelProviders.of(getActivity()).get(SharedViewModel.class);
  itemSelector.setOnClickListener(item -> {
   model.select(item);
  });
 }
}


public class DetailFragment extends Fragment {
 public void onCreate(Bundle savedInstanceState) {
  super.onCreate(savedInstanceState);
  SharedViewModel model = ViewModelProviders.of(getActivity()).get(SharedViewModel.class);
  model.getSelected().observe(this, {
   item ->
   // Update the UI.
  });
 }
}
```

Another way is to define an interface in your Fragment A, and let your Activity implement that Interface. Now you can call the interface method in your Fragment, and your Activity will receive the event. Now in your activity, you can call your second Fragment to update the textview with the received value.

**Source:** _developer.android.com_
### Q66: How can two distinct Android apps interact? ☆☆☆

**Answer:**
At the simplest level there are two different ways for apps to interact on Android: via Intents, passing data from one application to another; and through Services, where one application provides functionality for others to use.



**Source:** _developer.android.com_
### Q67: Isn't android's Bundle functionally equivalent with a Map? ☆☆☆

**Answer:**
First, a `Map` does not necessarily have `String` keys.

Second, while a `Map` can hold arbitrary objects, it cannot do so in a typesafe fashion. IOW, if you want the `Map` to hold strings, integers, and so forth, you will need to keep casting the results of `get()` calls, because your `Map` would have to be `Map<String, Object>`.

Third, `Bundle` implements `Parcelable`, which is very important for Android IPC. `Map` is an interface and does not extend `Parcelable`. This allows Bundles to be used as service parameters and to be attached to intents / passed into activities.

**Source:** _stackoverflow.com_
### Q68: What is the difference between a Bundle and an Intent? ☆☆☆

**Answer:**
A **Bundle** is a collection of key-value pairs.

However, an **Intent** is much more. It contains information about an operation that should be performed. This new operation is defined by the action it can be used for, and the data it should show/edit/add. The system uses this information for finding a suitable app component (activity/broadcast/service) for the requested action.

Think of the Intent as a Bundle that also contains information on who should receive the contained data, and how it should be presented.

**Source:** _stackoverflow.com_
### Q69: What is a LocalBroadcastManager? ☆☆☆

**Answer:**
It is good practice to use broadcast receivers when you want to send or receive data between different applications. But if the communication is limited to your application then it is not good to use the global broadcast.

In this case Android provides local broadcasts with the **LocalBroadcastManager** class. Using global broadcast, any other application can also send and receives broadcast messages to and from our application. This can be a serious security thread for our application. Also global broadcast is sent system-wide, so it is not performance efficient.

The **LocalBroadcastManager** is much more efficient as it doesn’t need inter-process communication.
Below are some of its benefits:
* Broadcast data won’t leave your app, so don’t need to worry about leaking private data.
* It is not possible for other applications to send these broadcasts to your app, so you don’t need to worry about having security holes they can exploit.
* It is more efficient than sending a global broadcast through the system.
* No overhead of system-wide broadcast.

**Source:** _android.jlelse.eu_
### Q70: What is a JobScheduler? ☆☆☆

**Answer:**
The **JobScheduler** API performs an operation for your application when a set of predefined conditions are met (such as when a device is plugged into a power source or connected to a Wi-Fi network). This allows your app to perform the given task while being considerate of the device's battery at the cost of timing control. 

Unlike the **AlarmManager** class, the timing isn't exact. Compared to a custom **SyncAdapter** or the **AlarmManager**, the JobScheduler supports batch scheduling of jobs. The Android system can combine jobs so that battery consumption is reduced. JobManager makes handling uploads easier as it handles automatically the unreliability of the network. It also survives application restarts. Here are example when you would use this job scheduler:
* Tasks that should be done once the device is connect to a power supply
* Tasks that require network access or a Wi-Fi connection.
* Task that are not critical or user facing
* Tasks that should be running on a regular basis as batch where the timing is not critical

**Source:** _stackoverflow.com_
### Q71: What is DDMS and what can you do with it? ☆☆☆

**Answer:**
The **Dalvik Debug Monitor Service (DDMS)** is a debugging tool used in the Android platform. The Dalvik Debug Monitor Service is downloaded as part of the Android SDK. Some of the services provided by the DDMS are port forwarding, on-device screen capture, on-device thread and heap monitoring, and radio state information.

The main services provided by Dalvik Debug Monitor Server are:
* App memory usage statistics (total heap and object allocation statistics)
* App thread statistics
* Device screen capture
* Device file explorer
* Incoming call and SMS spoofing
* Location data spoofing
* Logcat

**Source:** _www.toptal.com_
### Q72: What is the support library? Why was it introduced? ☆☆☆

**Answer:**
The **Support Library** is generally used when you want to easily support a wider range of OS versions with less version specific source - with it you can use features introduced in higher version of the OS on older platforms without having to worry and check whether this platform has that feature and do something in case it doesn't.

You should use one of the support libraries when you need specific framework features that are newer than the minSdkVersion of your app or that are not available in the standard framework.

The compatibility libraries largely use shims to back port features. These compatibility shims are thin wrappers around components that pass calls through to the underlying framework implementation if used on a release that supports the API. On older releases, the shims instead call the support implementation, perhaps with slightly different or reduced functionality.

**Source:** _stackoverflow.com_
### Q73: What is Android Data Binding? ☆☆☆

**Answer:**
The **Data Binding Library** is a _support library_ that allows you to bind UI components in your layouts to data sources in your app using a declarative format rather than programmatically.

Layouts are often defined in activities with code that calls UI framework methods. For example, the code below calls findViewById() to find a TextView widget and bind it to the userName property of the viewModel variable:

```java
TextView textView = findViewById(R.id.sample_text);
textView.setText(viewModel.getUserName());
```
The following example shows how to use the Data Binding Library to assign text to the widget directly in the layout file. This removes the need to call any of the Java code shown above.
```java
<TextView
    android:text="@{viewmodel.userName}" />
```

The pros of using Android Data Binding:
* Reduces boilerplate code which in turns brings
 * Less coupling
 * Stronger readability
* Powerful, easy to implement custom attribute and custom view
* Even faster than `findViewById` - The binding does a single pass on the View hierarchy, extracting the Views with IDs. This mechanism can be faster than calling findViewById for several Views.

**Source:** _developer.android.com_
### Q74: What are dex files are used for? ☆☆☆

**Answer:**
A `.java` file is given to the java compiler (javac) to generate the .class file. All `.class` files are given to dx tool to generate a single `dex` file. The `dex` file is given to the Dalvik VM to generate the final machine code. The final machine code is given to the CPU to execute.

`.apk` file contains `.dex` file in zip format which can be run on Dalvik VMs

<div class="text-center"/>
<img src="https://i.stack.imgur.com/CnNSD.png" class="img-fluid"/>
</div>


**Source:** _stackoverflow.com_
### Q75: How would you preserve Activity state during a screen rotation? ☆☆☆

**Answer:**
When your orientation changes, you don't have to manually change to the landscape layout file. Android does this automatically for you. When orientation changes, Android destroys your current activity and creates a new activity again, this is why you are losing the text.

Basically, whenever Android destroys and recreates your Activity for orientation change, it calls `onSaveInstanceState()` before destroying and calls `onCreate()` after recreating. Whatever you save in the bundle in onSaveInstanceState, you can get back from the `onCreate()` parameter.

```java
private TextView mTextView;
private static final String KEY_TEXT_VALUE = "textValue";

@Override
protected void onCreate(Bundle savedInstanceState) {
   super.onCreate(savedInstanceState);
   mTextView = (TextView) findViewById(R.id.main);
   if (savedInstanceState != null) {
      CharSequence savedText = savedInstanceState.getCharSequence(KEY_TEXT_VALUE);
      mTextView.setText(savedText);
   }
}

@Override
protected void onSaveInstanceState (Bundle outState) {
    super.onSaveInstanceState(outState);
    outState.putCharSequence(KEY_TEXT_VALUE, mTextView.getText());
}
```

**Source:** _stackoverflow.com_
### Q76: Describe Different Types of Services in Android ☆☆☆

**Answer:**
A **Service** is an application component that can perform long-running operations in the background, and it doesn't provide a user interface. It can run in the background, even when the user is not interacting with your application. These are the three different types of services:

*   **Foreground Service:** A foreground service performs some operation that is noticeable to the user. For example, we can use a foreground service to play an audio track.
*   **Background Service:** A background service performs an operation that isn’t directly noticed by the user. In Android API level 26 and above, there are restrictions to using background services and it is recommended to use *WorkManager* in these cases.
*   **Bound Service:** A service is bound when an application component binds to it by calling `bindService()`. A bound service offers a client-server interface that allows components to interact with the service, send requests, receive results. A bound service runs only as long as another application component is bound to it.

**Source:** _android.jlelse.eu_
### Q77: What is the difference between Service & Intent Service? ☆☆☆

**Answer:**
*   **Service** is the base class for Android services that can be extended to create any service. A class that directly extends Service runs on the main thread so it will block the UI (if there is one) and should therefore either be used only for short tasks or should make use of other threads for longer tasks.
*   **IntentService** is a subclass of **Service** that handles asynchronous requests (expressed as “Intents”) on demand. Clients send requests through startService(Intent) calls. The service is started as needed, handles each Intent in turn using a worker thread, and stops itself when it runs out of work.

**Source:** _android.jlelse.eu_
### Q78: What are retained fragments? ☆☆☆

**Answer:**
By default, Fragments are destroyed and recreated along with their parent Activity’s when a configuration change occurs. Calling `setRetainInstance(true)` allows us to bypass this destroy-and-recreate cycle, signaling the system to retain the current instance of the fragment when the activity is recreated.

**Source:** _android.jlelse.eu_
### Q79: How would you support different screen sizes? ☆☆☆

**Answer:**
*   **Create a flexible layout** — The best way to create a responsive layout for different screen sizes is to use ConstraintLayout as the base layout in your UI. ConstraintLayout allows you to specify the position and size for each view according to spatial relationships with other views in the layout. This way, all the views can move and stretch together as the screen size changes.
*   **Create stretchable nine-patch bitmaps**
*   **Avoid hard-coded layout sizes** — Use wrap\content or match\parent. **Create alternative layouts** — The app should provide alternative layouts to optimise the UI design for certain screen sizes. For eg: different UI for tablets
*   **Use the smallest width qualifier** — For example, you can create a layout named main\activity that’s optimised for handsets and tablets
*   The smallest width qualifier specifies the smallest of the screen’s two sides, regardless of the device’s current orientation, so it’s a simple way to specify the overall screen size available for your layout.

**Source:** _android.jlelse.eu_
### Q80: What are the permission protection levels in Android? ☆☆☆

**Answer:**
*   **Normal** — A lower-risk permission that gives requesting applications access to isolated application-level features, with minimal risk to other applications, the system, or the user. The system automatically grants this type of permission to a requesting application at installation, without asking for the user’s explicit approval.
*   **Dangerous** — A higher-risk permission. Any dangerous permissions requested by an application may be displayed to the user and require confirmation before proceeding, or some other approach may be taken to avoid the user automatically allowing the use of such facilities.
*   **Signature** — A permission that the system grants only if the requesting application is signed with the same certificate as the application that declared the permission. If the certificates match, the system automatically grants the permission without notifying the user or asking for the user’s explicit approval.
*   **SignatureOrSystem** — A permission that the system grants only to applications that are in the Android system image or that are signed with the same certificate as the application that declared the permission.

**Source:** _android.jlelse.eu_

### Q81: What are some best practices to avoid memory leaks on Android? ☆☆☆☆

**Answer:**
To avoid context-related memory leaks, remember the following:

* Do not keep long-lived references to a context-activity (a reference to an activity should have the same life cycle as the activity itself)
* Try using the context-application instead of a context-activity
* Avoid non-static inner classes in an activity if you don't control their life cycle, use a static inner class and make a weak reference to the activity inside. The solution to this issue is to use a static inner class with a WeakReference to the outer class, as done in ViewRoot and its W inner class for instance
* A garbage collector is not an insurance against memory leaks

**Source:** _stackoverflow.com_
### Q82: What are some difference between Parcelable and Serializable? ☆☆☆☆

**Answer:**
In Android we cannot just pass objects to activities. To do this the objects must either implement `Serializable` or `Parcelable` interface.

* **Serializable** is a standard Java interface. You can just implement Serializable interface and add override methods. The problem with this approach is that reflection is used and it is a slow process. 

* **Parcelable** process is much faster than Serializable. One of the reasons for this is that we are being explicit about the serialization process instead of using reflection to infer it. It also stands to reason that the code has been heavily optimized for this purpose.

Also consider:

* Parcelable is faster than Serializable interface
* Parcelable interface takes more time to implement compared to Serializable interface
* Serializable interface is easier to implement
* Serializable interface creates a lot of temporary objects and causes quite a bit of garbage collection
* Parcelable array can be passed via Intent

**Source:** _stackoverflow.com_
### Q83: What are best practices for storing and protecting private API keys in applications? ☆☆☆☆

**Details:**
Assuming I have something similar to this, how can I protect the secret key:

```java
public class DropboxService  {

    private final static String APP_KEY = "jk433g34hg3";
    private final static String APP_SECRET = "987dwdqwdqw90";
    private final static AccessType ACCESS_TYPE = AccessType.DROPBOX;

    // SOME MORE CODE HERE

}
```
What is in your opinion the best and most secure way to store the private key? Obfuscation, encryption, what do you think?

**Answer:**
If you want to protect your secret, not having it in your app in the first place is a pretty good way to go. Few ideas, in my opinion only first one gives some guarantee:

1. Create server-side API for all 3-rd party requests. When your client wants to make an API call, it asks the app auth service to authenticate it (using strong remote attestation techniques), and it receives a time limited (usually JWT) token signed by the secret.The token is sent with each API call where the endpoint can verify its signature before acting on the request. 
1. Keep your secrets on some server on internet, and when needed just grab them and use. If user is about to use dropbox then nothing stops you from making request to your site and get your secret key.
2. Put your secrets in jni code, add some variable code to make your libraries bigger and more difficult to decompile. You might also split key string in few parts and keep them in various places.
3. Use obfuscator, also put in code hashed secret and later on unhash it when needed to use.
4. ut your secret key as last pixels of one of your image in assets. Then when needed read it in your code. Obfuscating your code should help hide code that will read it.

**Source:** _stackoverflow.com_
### Q84: Provide some tips to reduce battery usage in an android application ☆☆☆☆

**Answer:**
Tips for improving battery usage in an android application:

* **Reduce network calls** as much as you can: Cache your data and retrieve it from the cache when required next time.
* **Avoid wake lock as much as possible**: A wake lock is a mechanism to indicate that your application needs to have the device stay on.
* **Use AlarmManager carefully**: Wrong use of AlarmManager can easily drain the battery.
* **Batch the network calls**: You should batch the network calls if possible so that you can prevent the device from waking every second.
* **A Different logic for Mobile Data and Wifi**: You should write different logic for mobile data and wifi as one logic may be optimized for mobile data and other may be optimized for wifi.
* **Check all background processes**: You should check all the background processes.
* **Use GPS carefully**: Do not use it frequently, use it only when actually required.
* **Use JobScheduler**: This is an API for scheduling various types of jobs against the framework that will be executed in your application’s own process. The framework will be intelligent about when you receive your callbacks and attempt to batch and defer them as much as possible.

**Source:** _blog.mindorks.com_
### Q85: When to use SparseArray vs HashMap? ☆☆☆☆

**Answer:**
**SparseArray** can be used to replace **HashMap** when the key is a primitive type. A Sparse array in Java is a data structure which maps keys to values. Same idea as a Map, but different implementation:

A Sparse Array is simply made of two arrays: an arrays of (primitives) keys and an array of (objects) values. There can be gaps in these arrays indices, hence the term “sparse” array.

```java
class SparseIntArray {
    int[] keys;
    int[] values;
    int size;
}
```

The main interest of the SparseArray is that it saves memory by using primitives instead of objects as the key.

Benefits are:
* Allocation-free
* No boxing

Drawbacks:
* Generally slower, not indicated for large collections
* They won't work in a non-Android project

**HashMap** can be replaced by the following:
```java
SparseArray          <Integer, Object>
SparseBooleanArray   <Integer, Boolean>
SparseIntArray       <Integer, Integer>
SparseLongArray      <Integer, Long>
LongSparseArray      <Long, Object>
LongSparseLongArray  <Long, Long>   //this is not a public class                                 
                                    //but can be copied from  Android source code
```

**Source:** _stackoverflow.com_
### Q86: What is the difference between ArrayMap vs HashMap?  ☆☆☆☆

**Answer:**
**ArrayMap** is a generic key->value mapping data structure that is designed to be more memory efficient than a traditional Java **HashMap**. It keeps its mappings in an array data structure — an integer array of hash codes for each item, and an Object array of the key/value pairs. This allows it to avoid having to create an extra object for every entry put into the map, and it also tries to control the growth of the size of these arrays more aggressively (since growing them only requires copying the entries in the array, not rebuilding a hash map).

That this implementation is not intended to be appropriate for data structures that may contain large numbers of items. It is generally slower than a traditional HashMap since lookups require a binary search and add and removes require inserting and deleting entries in the array. For containers holding up to hundreds of items, the performance difference is not significant, less than 50%.

**Source:** _medium.com_
### Q87: Explain how ArrayMap works ☆☆☆☆

**Answer:**
ArrayMap uses 2 arrays. The instance variables used internally are Object\[ \] mArray to store the objects and the int\[\] mHashes to store hashCodes. When a key/value is inserted :

*   Key/Value is autoboxed.
*   The key object is inserted in the mArray where on the index in which it needs to pushed is searched using the binary search. (Thanks [Or Gilad](/@gilador84) for correcting it).
*   A value object is also inserted in the position next to key’s position in mArray\[ \].
*   The hashCode of the key is calculated and placed in mHashes\[ \] at the next available position.

_For searching a key :_

*   Key’s hashCode is calculated
*   Binary search is done for this hashCode in the mHashes array. This implies time complexity increases to O(logN).
*   Once we get the index of hash, we know that key is at 2\*index position in mArray and value is at 2\*index+1 position.
*   Here the time complexity increases from O(1) to O(logN), but it is memory efficient. Whenever we play on a dataset of around 100,
*   there will no problem of time complexity, it will be non-noticeable. As we have the advantage of memory efficient application.

**Source:** _medium.com_
### Q88: Why to consider FlatBuffers over JSON? ☆☆☆☆

**Answer:**
**FlatBuffers** are an efficient cross platform serialization library. They were originally created at Google for game development, and other performance-critical applications.

Why use FlatBuffers?
* **Access to serialized data without parsing/unpacking** — What sets FlatBuffers apart is that they represent hierarchical data in a flat binary buffer, in such a way that they can still be accessed directly without parsing and unpacking, while also still supporting data structure evolution (forwards/backwards compatibility).
* **Memory efficiency and speed** — The only memory needed to access your data is that of the buffer. It requires zero additional allocations (at least in C++. Other languages may vary). FlatBuffers are also suitable for use with mmap (or streaming), requiring only part of the buffer to be in memory. 
* **Tiny code footprint** — FlatBuffers require only small amounts of generated code, and just a single small header as the minimum dependency, which is very easy to integrate.
* **Strongly typed** — Errors happen at compile time rather than manually having to write repetitive and error prone run-time checks. Useful code can be generated for you.

I have tried to parse 4 mb of JSON file with both FlatBuffer and JSON. FlatBuffer tooks 1–5 ms and JSON took around 2000ms.And no GC was called in android app during FlatBuffer use. But GC was called so many time while using JSON. So, UI was freezing in case of JSON (only option left with JSON is to parse it in background thread).

**Source:** _blog.mindorks.com_
### Q89: What are some differences between ART and Dalvik? ☆☆☆☆

**Answer:**
* **Approach**: ART uses AOT(Ahead Of Time) approach and compiles the whole code during the installation time but the Dalvik uses JIT(Just In Time) approach and complies only a part of the code during installation and rest of the code will be compiled dynamically.
* **Booting time**: As compare to Dalvik, ART takes more time to reboot because the cache is built at the first time. So, the booting is slow.
* **Space**: Since ART uses the AOT approach, so it needs more space during installation. While Dalvik uses the JIT approach, so for mobile phones having less storage can use the Dalvik.
* **Battery**: ART increases battery performance to a large extent because of the AOT approach. While the Dalvik uses the JIT approach and this results in more battery utilization.
* **Garbage Collection**: ART has better garbage collection than Dalvik.

**Source:** _blog.mindorks.com_
### Q90: What is Broadcast Receiver? ☆☆☆☆

**Answer:**
Android apps can send or receive broadcast messages from the Android system and other Android apps, similar to the publish-subscribe design pattern. **Broadcast Receiver** which is also known as receiver is a component of android application. With this component we can register receivers for any system-level or application-level event. Once that event occurs, android system will notify the registered receivers about the execution of events respectively.

There are two types of broadcasts received by receivers and they are:
1. Normal Broadcasts
2. Ordered Broadcasts

**Source:** _stackoverflow.com_
### Q91: What is the difference between Android timer and a Handler to do action every N seconds? ☆☆☆☆

**Answer:**
`android.os.Handler` is part of Android framework, the job will execute on the UI or main thread if you have created the Handler in the UI or main thread. Note that in Android you can only update views from the UI thread.

`java.util.Timer `on the other hand will execute on another thread so it cannot update the views.

So Handler is the recommended here. If you really want to use Timer you have to use `runOnUiThread` like:

```java
new Timer().schedule(new TimerTask() {
    @Override
    public void run() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                //this will run on UI thread so you can update views here
            }
        });
    }
}, 2000, 2000);
```

**Source:** _stackoverflow.com_
### Q92: Can you manually call the Garbage collector? ☆☆☆☆

**Answer:**
It is never a good practice to call the GC manually. Dalvik or ART simply knows better than us. If you are facing memory issues, try to find memory leaks in your app using MAT.

Also invoking `System.gc()` is not a guarantee of garbage collection actually being performed. It's more of a hint than anything else.

**Source:** _stackoverflow.com_
### Q93: When is it necessary, or better to use a SurfaceView instead of a View? ☆☆☆☆

**Answer:**
**Views** are all drawn on the same GUI thread which is also used for all user interaction. The main difference is that **SurfaceView** can be drawn on _by background theads_ but Views can't. **SurfaceViews** contain a nice rendering mechanism that allows threads to update the surface's content without using a handler (good for animation).

There are more you might care.

 - surfaceView has dedicate surface buffer while all the view shares one surface buffer that is allocated by ViewRoot. In another word, surfaceView cost more resources.
 - surfaceView cannot be hardware accelerated (as of JB4.2) while 95% operations on normal View are HW accelerated using openGL ES.
 - More work should be done to create your customized surfaceView. You need to listener to the surfaceCreated/Destroy Event, create an render thread, more importantly, synchronized the render thread and main thread. However, to customize the View, all you need to do is override `onDraw` method.
 - The timing to update is different. Normal view update mechanism is constraint or controlled by the framework:You call `view.invalidate` in the UI thread or `view.postInvalid` in other thread to indicate to the framework that the view should be updated. However, the view won't be updated immediately but wait until next VSYNC event arrived. The easy approach to understand VSYNC is to consider it is as a timer that fire up every 16ms for a 60fps screen. In Android, all the normal view update (and display actually but I won't talk it today), is synchronized with VSYNC to achieve better smoothness. Now,back to the surfaceView, you can render it anytime as you wish. However, I can hardly tell if it is an advantage, since the display is also synchronized with VSYNC, as stated previously.

**Source:** _stackoverflow.com_
### Q94: What is the StrictMode? ☆☆☆☆

**Answer:**
**StrictMode** is a special class for verifying that your Android application is not doing things like disk I/O, Network access from the UI thread. This is a debugging feature introduced in Android 2.3. This developer tool detect things done accidentally and bring them to your attention so that you can fix them so as to avoid ANR dialogs(Activity Not Responding dialogs). 

**StrictMode** is used to setup thread and virtual machine policies for your application and report violations of such policies. You will get an alert if a policy is violated. You can instruct Android to crash your application with the alert or you can just log the alert and let your application carry on.

**Source:** _javabeat.net_
### Q95: What is the Android NDK? How can one use it? Why should one use it? ☆☆☆☆

**Answer:**
The **NDK** (Native Development Kit) is a tool that allows you to program in C/C++ for Android devices. It's intended to integrate with the SDK (it's described as a "companion tool") and used only for performance-critical portions of a project. Many multimedia applications and video games use native code for processor-intensive tasks. 

The performance improvements can come from three sources:

* **Firstly**, the native code is compiled to a binary code and run directly on OS, while Java code is translated into Java byte-code and interpreted by Dalvik Virtual Machine (VM). At Android 2.2 or higher, a Just-In-Time (JIT) compiler is added to Dalvik VM to analyze and optimize the Java byte-code while the program is running (for example, JIT can compile a part of the byte-code to binary code before its execution). But in many cases, native code still runs faster than Java code.
* The **second** source for performance improvements at NDK is that native code allows developers to make use of some processor features that are not accessible at Android SDK, such as NEON, a Single Instruction Multiple Data (SIMD) technology, allowing multiple data elements to be processed in parallel.
* The **third** aspect is that we can optimize the critical code at an assembly level, which is a common practice in desktop software development.

**Source:** _stackoverflow.com_
### Q96: What is Doze? What about App Standby? ☆☆☆☆

**Answer:**
Starting from Android 6.0 (API level 23), Android introduces two power-saving features that extend battery life for users by managing how apps behave when a device is not connected to a power source. 

**Doze** reduces battery consumption by deferring background CPU and network activity for apps when the device is unused for long periods of time.  In Doze mode, the system attempts to conserve battery by restricting apps' access to network and CPU-intensive services. It also prevents apps from accessing the network and defers their jobs, syncs, and standard alarms.

Periodically, the system exits Doze for a brief time to let apps complete their deferred activities. During this maintenance window, the system runs all pending syncs, jobs, and alarms, and lets apps access the network. 

**App Standby** defers background network activity for apps with which the user has not recently interacted. App Standby allows the system to determine that an app is idle when the user is not actively using it. The system makes this determination when the user does not touch the app for a certain period of time. When the user plugs the device into a power supply, the system releases apps from the standby state, allowing them to freely access the network and to execute any pending jobs and syncs. If the device is idle for long periods of time, the system allows idle apps network access around once a day.

**Source:** _stackoverflow.com_
### Q97: What are Android Architecture Components? ☆☆☆☆

**Answer:**
**Android architecture components** are a collection of libraries that help you design robust, testable, and maintainable apps. Android Architecture Components are a part of **Android Jetpack**.

All the Android Architecture Components are as follows:

* **Data Binding**: It helps in declaratively binding UI elements to in our layout to data sources of our app.
* **Lifecycles**: It manages activity and fragment lifecycles of our app, survives configuration changes, avoids memory leaks and easily loads data into our UI.
* **LiveData**: It notifies views of any database changes. Use LiveData to build data objects that notify views when the underlying database changes.
* **Navigation**: It handles everything needed for in-app navigation in Android application.
* **Paging**: It helps in gradually loading information on demand from our data source.
* **Room**: It is a SQLite object mapping library. Use it to Avoid boilerplate code and easily convert SQLite table data to Java objects. Room provides compile time checks of SQLite statements and can return RxJava, Flowable and LiveData observables.
* **ViewModel**: It manages UI-related data in a lifecycle-conscious way. It stores UI-related data that isn't destroyed on app rotations.
* **WorkManager**: It manages every background jobs in Android with the circumstances we choose.

**Source:** _developer.android.com_
### Q98: What is the difference between ANR and crash in Android? ☆☆☆☆

**Answer:**
ANR stands for **A**pplication **N**ot **R**esponding. 

An ANR will occur if you are running a process on the UI thread which takes a long time, usually around 5 seconds. During this time the GUI (Graphical User Interface) will lock up which will result in anything the user presses will not be actioned. After the 5 seconds approx has occurred, if the thread still hasn't recovered then an ANR dialogue box is shown informing the user that the application is not responding and will give the user the choice to either wait, in the hope that the app will eventually recover, or to force close the app. 

A crash is when an exception within the app has been thrown which has not been handled. For example, if you try to set the text of an `EditText` component, but the `EditText` is null and there is no try catch statement to catch the exception that your app will crash and will be force closed. The user will not see what caused the crash, they will be shown a dialogue telling that the app has force closed unexpectedly and will give them the option to send a bug report. In this example if you were to look in the bug report you would see the error caused by `java.lang.NullPointerException`. 

**Source:** _stackoverflow.com_
### Q99: How do you handle Bitmaps in Android as it takes too much memory? ☆☆☆☆

**Answer:**
There are a number of reasons why loading bitmaps in your Android app is tricky:
* Bitmaps can very easily exhaust an app's memory budget. 
* Loading bitmaps on the UI thread can degrade your app's performance, causing slow responsiveness or even ANR messages.
* If your app is loading multiple bitmaps into memory, you need to skillfully manage memory and disk caching. 

For most cases, we recommend that you use the Glide library to fetch, decode, and display bitmaps in your app. Glide abstracts out most of the complexity in handling these and other tasks related to working with bitmaps and other images on Android.

**Source:** _developer.android.com_
### Q100: Is a Dalvik virtual machine instance created for each application? ☆☆☆☆

**Answer:**
Every Android application runs in its own process, with **its own instance** of the Dalvik virtual machine. Dalvik has been written so that a device can run multiple VMs efficiently.

The Dalvik VM executes files in the Dalvik Executable (.dex) format which is optimised for minimal memory footprint.

The VM is register-based, and runs classes compiled by a Java language compiler that have been transformed into the .dex format by the included dx tool.

**Source:** _stackoverflow.com_

### Q101: Explain when would you call getApplicationContext() and why? ☆☆☆☆☆

**Answer:**
You *only* use `getApplicationContext()` when you *know* you need a `Context` for something that may live longer than any other likely `Context` you have at your disposal. Scenarios include:

 - Use `getApplicationContext()` if you need something tied to a `Context` that itself will have global scope. I use `getApplicationContext()`, for example, in `WakefulIntentService`, for the static `WakeLock` to be used for the service. Since that `WakeLock` is static, and I need a `Context` to get at `PowerManager` to create it, it is safest to use `getApplicationContext()`.

 - Use `getApplicationContext()` when you bind to a `Service` from an `Activity`, if you wish to pass the `ServiceConnection` (i.e., the handle to the binding) between `Activity` instances via `onRetainNonConfigurationInstance()`. Android internally tracks bindings via these `ServiceConnections` and holds references to the `Contexts` that create the bindings. If you bind from the `Activity`, then the new `Activity` instance will have a reference to the `ServiceConnection` which has an implicit reference to the old `Activity`, and the old `Activity` cannot be garbage collected.

- Some developers use custom subclasses of `Application` for their own global data, which they retrieve via `getApplicationContext()`. That's certainly possible. 



**Source:** _stackoverflow.com_
### Q102:  Explain reasons why not to use getApplicationContext()? ☆☆☆☆☆

**Answer:**
Here are reasons why *not* to use `getApplicationContext()` wherever you go:

 - It's not a complete `Context`, supporting everything that `Activity` does. Various things you will try to do with this `Context` will fail, mostly related to the GUI.

 - It can create memory leaks, if the `Context` from `getApplicationContext()` holds onto something created by your calls on it that you don't clean up. With an `Activity`, if it holds onto something, once the `Activity` gets garbage collected, everything else flushes out too. The `Application` object remains for the lifetime of your process.

See this table as a guidance for when to use the different types of Context:

<div class="text-center"/>
<img src="https://i.stack.imgur.com/1o5MI.png" class="img-fluid" />
</div>


**Source:** _stackoverflow.com_
### Q103: What is the relationship between Looper, Handler and MessageQueue in Android? ☆☆☆☆☆

**Answer:**
A `Looper` is a message handling loop: it reads and processes items from a `MessageQueue`. The `Looper` class is usually used in conjunction with a `HandlerThread` (a subclass of `Thread`).

A `Handler` is a utility class that facilitates interacting with a `Looper`&mdash;mainly by posting messages and `Runnable` objects to the thread's `MessageQueue`. When a `Handler` is created, it is bound to a specific `Looper` (and associated thread and message queue).

In typical usage, you create and start a `HandlerThread`, then create a `Handler` object (or objects) by which other threads can interact with the `HandlerThread` instance. The `Handler` must be created while running on the `HandlerThread`, although once created there is no restriction on what threads can use the `Handler`'s scheduling methods (`post(Runnable)`, etc.)

The main thread (a.k.a. UI thread) in an Android application is set up as a handler thread before your application instance is created.

The relationships between Looper, Handler and MessageQueue is shown below:


<div class="text-center"/>
<img src="https://i.stack.imgur.com/h4z38.jpg" class="img-fluid" />
</div>


**Source:** _stackoverflow.com_
### Q104: What is the onTrimMemory method? ☆☆☆☆☆

**Answer:**
Android can reclaim memory from your app in several ways or kill your app entirely if necessary to free up memory for critical tasks. To further help balance the system memory and avoid the system's need to kill your app process, you can implement the **ComponentCallbacks2** interface in your Activity classes.

`onTrimMemory() `callback method allows your app to listen for memory related events when your app is in either the foreground or the background, and then release objects in response to app lifecycle or system events that indicate the system needs to reclaim memory.

Sometimes to improve performance you have to increase memory usage, such as caching some data used by your activities. That's the type of resource you should release when `onTrimMemory` is called, so your app uses less memory, even if it affects performance. 

**Source:** _developer.android.com_
### Q105: What happens if the user navigates away or closes the app while I still have a reference to the Activity the user just closed in my AsyncTask? ☆☆☆☆☆

**Answer:**
Short answer - **Memory Leaks**. As long as some part of the app like an **AsyncTask** still holds a reference to the **Activity** it will not be destroyed. It will stick around until the AsyncTask is done or releases its reference in some other way. This can have very bad consequences like your app crashing, but the worst consequences are the ones you don't notice: your app may keep reference to Activities which should have been released ages ago and each time the user does whatever leaks the Activity the memory on the device might get more and more full until seemingly out of nowhere Android kills your app for consuming too much memory.

**Source:** _stackoverflow.com_
### Q106: What is Intent vs Sticky Intent vs Pending Intent?  ☆☆☆☆☆

**Answer:**
**Intent** - is a message passing mechanism between components of Android, except for Content Provider. You can use Intent to start any component.

**Sticky Intent** - Sticks with Android, for future broadcast listeners. For example if BATTERY_LOW event occurs then that Intent will stick with Android so that any future requests for BATTERY_LOW, will return the Intent.  the Intent you are sending stays around after the broadcast is complete, so that others can quickly retrieve that data through the return value of `registerReceiver(BroadcastReceiver, IntentFilter)`.

One example of a sticky broadcast sent via the operating system is ACTION_BATTERY_CHANGED. When you call registerReceiver() for that action — even with a null BroadcastReceiver — you get the Intent that was last Broadcast for that action. 

**Pending Intent** - If you want some one to perform any Intent operation at future point of time on behalf of you, then we will use Pending Intent.

**Source:** _stackoverflow.com_
### Q107: What is a Sticky Broadcast? ☆☆☆☆

**Answer:**
A normal broadcast Intent is not available anymore after is was send and processed by the system. If you use the `sendStickyBroadcast(Intent)` method, the **Intent is sticky**, meaning the Intent you are sending stays around after the broadcast is complete.

The value of a **sticky broadcast** is the value that was last broadcast and is currently held in the sticky cache. This is not the value of a broadcast that was received right now. I suppose you can say it is like a browser cookie that you can access at any time.

**Source:** _stackoverflow.com_
### Q108: What is the difference between Local, Normal, Ordered and Sticky broadcasts? ☆☆☆☆☆

**Answer:**
**Normal Broadcast**
- use `sendBroadcast()`
- asynchronous broadcast
- any receiver receives broadcast not any particular order

**Ordered Broadcast**
- use `sendOrderedBroadcast()`
- synchronous broadcast
- receiver receives broadcast in priority base
- we can also simply abort broadcast in this type

**Local Broadcast**
- use only when broadcast is used only inside same process

**Sticky Broadcast**
- normal broadcast intent is not available any more after this was send and processed by the system.
- use `sendStickyBroadcast(Intent)`
- the corresponding intent is sticky, meaning the intent you are sending stays around after the broadcast is complete.
- because of this others can quickly retrieve that data through the return value of `registerReceiver(BroadcastReceiver, IntentFilter)`
- apart from this same as `sendBroadcast(Intent)`

**Source:** _stackoverflow.com_
### Q109: How can I use AsyncTask in different Activities? ☆☆☆☆

**Answer:**
One of the methods using AsynTask in different Activities, creating a callback interface.

Create a callback interface
```java
interface AsyncTaskListener<T> {
    public void onComplete(T result);
}
```

Then in your **MainActivity** and **TestActivity**:
```java
public class MainActivity extends AppCompatActivity
       implements AsyncTaskListener<String> {

      public void onComplete(String result) {
              // your staff here
      }
}

public class TestActivity extends AppCompatActivity
       implements AsyncTaskListener<String> {

      public void onComplete(String result) {
              // your staff here
      }
}
```

And add to your **AsyncTask** class:
```java
public class JSONTask extends AsyncTask < String, String, String >
 private AsyncTaskListener < String > listener;

public JSONTask(AsyncTaskListener < String > callback) {
 this.listener = callback;
}

protected void onPostExecute(String result) {
 listener.onComplete(result); // calling onComplate interface
}
```

**Source:** _stackoverflow.com_
### Q110: What is AIDL? ☆☆☆☆

**Answer:**
The **Android Interface Definition Language (AIDL)** allows you to define the programming interface that both the client and service agree upon in order to communicate with each other using interprocess communication (IPC). On Android, one process cannot normally access the memory of another process. So to talk, they need to decompose their objects into primitives that the operating system can understand, and marshall the objects across that boundary for you. The code to do that marshalling is tedious to write, so Android handles it for you with AIDL.

**Source:** _developer.android.com_
### Q111: When would you use AIDL? ☆☆☆☆☆

**Answer:**
AIDL does nothing but lets the system to generate the boilerplate code that hides the binder IPC details, so that you can invoke the remote service API as a local method call. Using AIDL is necessary _only if you allow clients from different applications to access your service for IPC and want to handle multithreading_ in your service. So,

1. If you don't need IPC (i.e., your client and server stay in the same process), you don't need AIDL;
2. If you want to write the boilerplate code yourself for IPC, you don't need AIDL;
3. If your service is not complicated enough (i.e., does not require concurrent multithreaded accesses), you can use system provided Messenger API for IPC. You don't need your own AIDL, because the Messenger API hides the AIDL usage;
4. To extend the case 3, if you can use any existing lib or existing API to access a service in another process, you don't need your own AIDL. For example, you can access ActivityManagerService with existing system API, and all the AIDL stuff for IActivityManager is hidden by the system API.

**Source:** _stackoverflow.com_
### Q112: When to use AIDL vs Messenger Queue? ☆☆☆☆☆

**Answer:**
*   **AIDL** is for the purpose when you’ve to go application level communication for data and control sharing, a scenario depicting it can be: An app requires list of all contacts from Contacts app (content part lies here) plus it also wants to show the call’s duration and you can also disconnect it from that app (control part lies here).
*   In **Messenger Queues** you’re more IN the application and working on threads and processes to manage the queue having messages so no Outside services interference here.
*   Messenger is needed if you want to bind a remote service (e.g. running in another process).

**Source:** _android.jlelse.eu_
### Q113: What is a ThreadPool? And is it more effective than using several separate Threads? ☆☆☆☆

**Answer:**
Creating and destroying threads has a high CPU usage, so when we need to perform lots of small, simple tasks concurrently, the overhead of creating our own threads can take up a significant portion of the CPU cycles and severely affect the final response time. **ThreadPool** consists of a task queue and a group of worker threads, which allows it to run multiple parallel instances of a task.

Using ThreadPool is more efficient than having multiple operations waiting to run on a single thread, but it also helps you avoid the considerable overhead of creating and destroying a thread every time you require a worker thread.

**Source:** _android.jlelse.eu_

### Q114: Is there a size limit for a Bundle? ☆☆☆☆
**Answer**
It depends on the purpose of the bundle. The bundle itself is only limited by the amount of memory.

The two main uses for bundles are to pass information between components using intents and to save the state of activities.

1. Intents / Binders
When used to pass information between Android components the bundle is serialized into a binder transaction. The total size for all binder transactions in a process is 1MB. If you exceed this limit you will receive this fatal error "!!! FAILED BINDER TRANSACTION !!!"

It's recommend that you keep the data in these bundles as small as possible because it's a shared buffer, anything more than a few kilobytes should be written to disk.

Reference: https://android.googlesource.com/platform/frameworks/base/+/jb-release/core/jni/android_util_Binder.cpp

ALOGE("!!! FAILED BINDER TRANSACTION !!!");
        // TransactionTooLargeException is a checked exception, only throw from certain methods.
        // FIXME: Transaction too large is the most common reason for FAILED_TRANSACTION
        //        but it is not the only one.  The Binder driver can return BR_FAILED_REPLY
        //        for other reasons also, such as if the transaction is malformed or
        //        refers to an FD that has been closed.  We should change the driver
        //        to enable us to distinguish these cases in the future.
Reference: http://developer.android.com/reference/android/os/TransactionTooLargeException.html

The Binder transaction buffer has a limited fixed size, currently 1Mb, which is shared by all transactions in progress for the process. Consequently this exception can be thrown when there are many transactions in progress even when most of the individual transactions are of moderate size.

2. Saved Instance State ( Activity onSaveInstanceState, onPause etc. )
I found no limit in the size I could store in the bundle used to preserve Activity state. I did some tests and could successfully store about 175mb before I received an out of memory exception trying to allocate the data I was attempting to save.

**Update:** This research was performed in 2014, newer versions of Android may crash with bundles over 500kb

**Source:** _stackoverflow.com_

### Q115: Which class is useful in managing a long-running data load in a way that works correctly with the lifecycle of an Activity or Fragment? ☆☆☆☆
**Answer**
android.app.LoaderManager

### Q116: When creating a content provider, where is the provider authority specified? ☆☆☆☆
**Answer**
The provider element of the app manifest.

### Q117: Which method accesses the context tied to the lifecycle of the entire application? ☆☆☆☆
**Answer**
Activity.getApplicationContext()

### Q118: How many emulators can be running at the same time on a single host computer? ☆☆☆☆
**Answer**
No predefined limit

### Q119: What is the result of placing a TextView within a RelativeLayout without providing any layout-related attributes on the TextView? ☆☆☆☆
**Answer**
The TextView will be positioned at the top-left of the RelativeLayout.

### Q120: What is the result of placing a TextView within a RelativeLayout without providing any layout-related attributes on the TextView? ☆☆☆☆
**Answer**
The TextView will be positioned at the top-left of the RelativeLayout.

### Q121: When an emulator image is configured to have a secure digital (SD) card, what normally happens to the content of the SD card when the emulator is shut down? ☆☆☆☆
**Answer**
Content is saved to the host computer's disk.

### Q122: Which attribute value(s) need(s) to be added to the WebView element in a layout resource to disable the WebViews scrollbars? ☆☆☆☆
**Answer**
android:scrollbars="none"

### Q122: Which attribute is required for all component types defined in the application manifest? ☆☆☆☆
**Answer**
name

### Q123: Which Activity lifecycle event method is called immediately when the Activity comes to the foreground? ☆☆
**Answer**
onResume

### Q123: When using the Android Material theme, which of the following color palette values affects the color of the action bar? ☆☆
**Answer**
colorPrimary

### Q124: Which folder is the best choice for storing the application icon? ☆☆
**Answer**
res/mipmap

### Q125: If you have an existing application in the Play Store with a package name of com.pluralsight.example01, what will happen if you upload an Android application package (apk) with the package name com.pluralsight.example02? ☆☆
**Answer**
The new package will be considered a different application

### Q126: In an Android app, which class allows an Android component to request that an action be performed by another component? ☆☆
**Answer**
Intent

### Q127: What is the appropriate way to request permissions for your application? ☆☆
**Answer**
<uses-permission> in the android manifest.
    
### Q128: Which permission is automatically granted by the system to your app if it is added in the app manifest?  ☆☆
**Answer**
VIBRATE

### Q129: When specifiying the android:id attribute value for a widget within a layout file, sometimes the android:id attribute value begins with "@id/" and other times it begins with "@+id/". What's the difference?  ☆☆
**Answer**
Using "@+id/" will create the identifier if it does not already exist

### Q130: When a new version of your application is uploaded to the Google Play Store, how long does it normally take for the new version to become available for updates and downloads? ☆☆
**Answer**
A few hours.

### Q131: In the case of a custom view that supports attributes, what must the custom view provide to allow the custom attributes to be used within a layout resource? ☆☆
**Answer**
A declare-styleable resource

### Q132: Which action should be supported to allow a user to scroll a list through multiple screens of content with a single finger motion?
**Answer**
Fling
