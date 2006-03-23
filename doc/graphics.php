<?php
require_once("docutil.php");
page_head("The BOINC graphics API");
echo"
<p>
BOINC applications can optionally provide graphics,
which are displayed either in an application window
or in a full-screen window (when acting as a screensaver).

<p>
General comments about graphics:
<ul>

<li>
It is desirable for the graphics to provide a
visualization of what the application is currently doing.
Usually the easiest way to do this is for
the graphics code to run concurrently with the science code,
and to share data structures with it.
This can be done using any of several <b>process structures</b>.
For example, you can use separate threads in a single address space,
or shared memory between separate programs.
BOINC supports various process structures (see below).

<li>
Whatever process structure is used, the application needs
to handle 'graphics messages' from the core client,
telling it when to open and close windows.

<li>
You are encouraged to implement graphics using OpenGL.
This makes it possible for your application to show graphics on all platforms.

<li>
Graphics on Unix is tricky because hosts
may not have the needed libraries (OpenGL, GLUT, X11).
If an application is linked dynamically to these libraries,
it will fail on startup if the libraries are not present.
On the other hand,
if an application is linked statically to these libraries,
graphics will be done very inefficiently on most hosts.
</ul>


<p>
BOINC supports process structures where graphics is done:
<ul>
<li> In a <a href=#monolithic>monolithic</a> program.
This works fine for Windows.
Not recommended for Unix because of the dynamic linking problem
described above.
<li> In a <a href=#shared_library>shared library</a>
that is dynamically linked by your main program.
This works well on Unix.
<li> In a <a href=#separate>separate program</a>.
This works on all platforms and provides a nice factorization,
but it introduces some complications that require work on your part.
</ul>
You can use different structures for different platforms.
For example, SETI@home uses monolithic on Windows
and shared library on other platforms.
Climateprediction.net uses a separate program on all platforms.

<a name=monolithic>
<h2>Process structures</h2>
<h3>Monolithic structure</h3>
<p>
In this approach, graphics are generated by a thread
within your main application.
The application must call either
".html_text("
    int boinc_init_graphics(WORKER_FUNC_PTR worker);
        // for simple applications
    int boinc_init_options_graphics(BOINC_OPTIONS&, WORKER_FUNC_PTR worker);
        // for compound applications
")."
where <code>worker()</code> is the main function of your application.
Do NOT call boinc_init() or boinc_init_options().
Your application must be linked with libboinc_graphics_api.a,
and with your rendering and input-handling functions (see below).
It should be linked dynamically with glut and opengl.
<p>
<code>boinc_init_graphics()</code> creates a <b>worker thread</b>
that runs the main application function.
The original thread becomes the <b>graphics thread</b>,
which handles GUI events and does rendering.
The two threads communicate through application-defined
shared memory structures.
Typically these structures contain information about the computation,
which is used to generate graphics.
You must initialize the shared data structure
before calling <code>boinc_init_graphics()</code>.
<p>
Unix/Linux applications that use graphics should compile
all files with -D_REENTRANT,
since graphics uses multiple threads.

<a name=shared_library>
<h3>Shared-library structure</h3>
<p>
In this structure your application consists of two parts:
a main program and a shared library.
The main program calls either
".html_text("
int boinc_init_graphics_lib(WORKER_FUNC_PTR worker, char* argv0);
    // for simple apps
int boinc_init_options_graphics_lib(
    BOINC_OPTIONS&, WORKER_FUNC_PTR worker, char* argv0
)
    // for compound apps
")."
where <code>worker()</code> is as above, and argv0 is the name of the
executable as passed in the second argument of main() as argv[0].
The main program must be linked with libboinc_graphics_lib.a

<p>
The shared library must have the same name as the
executable followed by '.so'.
It must be linked with libboinc_graphics_impl.a,
with your rendering and input-handling functions,
and (dynamically) with glut and opengl.

<p> 
You must bundle the main program and the shared library together as a
<a href=tool_update_versions.php>multi-file application version</a>.

<p>
A typical linking line in building the main program might look like
this:<br> <b>g++ -pthread -o einstein_4.01_i686-pc-linux-gnu app1.o
app2.o -lboinc_zip -lboinc_api -lboinc -lboinc_graphics_lib -ldl
-lm</b><br>
where app1.o and app2.o contain the definitions of main() and worker().

<p>
A typical linking line in building the shared library might
look like this:<br> <b>g++ -pthread -o
einstein_4.01_i686-pc-linux-gnu.so -shared -fPIC app_graphics1.o
app_graphics2.o -lboinc_graphics_impl -lboinc -lglut -lGLU -lGL -lX11
-lXmu -ldl -lm</b><br>
where app_graphics1.o and app_graphics2.o contain the definitions
of app_graphics_init(), app_graphics_render(), etc.

<p>In order to communicate data between the worker thread and the
graphics thread, the worker() function can call functions from within
the shared library.  To do this, it makes use of the global variable
graphics_lib_handle.  If NULL, this means that the host lacks graphics
capabilities.  If not NULL, the worker can use
<pre>
communications_function_hook = dlsym(graphics_lib_handle,\"communications_function\");
</pre>
to resolve pointers to functions which are defined in the graphics
code app_graphics.o.
In turn, such functions can modify data used by the graphics code.



<a name=separate>
<h3>Separate-program structure</h3>
<p>
In this approach, an application bundles a
'main program' and a 'graphics program'.
The main program executes the graphics program,
and kills it when done.
The main and graphics programs typically communicate using shared memory;
you can use the functions in boinc/lib/shmem.C for this.
<p>
The graphics application can be implemented
using the BOINC framework, in which case it must initialize with
".html_text("
    int boinc_init_options_graphics(BOINC_OPTIONS&, NULL);
")."
and supply rendering and input-handling functions.

<p>
Either the graphics or the main program can handle
graphics messages from the core client.
It's easiest to have the graphics program handle them;
if the main program handles them, it must convey them to the graphics program.

<p>


<h2>Rendering and input-handling functions</h2>
<p>
Programs that use BOINC graphics must supply the following functions:
<pre>
    int app_graphics_render(int xs, ys, double time_of_day);
</pre>
This will be called periodically in the graphics thread.
It should generate the current graphic.
<code>xs</code> and <code>ys</code> are the X and Y sizes of the window,
and <code>time_of_day</code> is the relative time in seconds.
The function should return true if it actually drew anything.
It can refer to the user name, CPU time etc. obtained from
<code>boinc_get_init_data()</code>.
Applications that don't do graphics must also supply a
dummy <code>app_graphics_render()</code> to link with the API.
<pre>
    void app_graphics_init();
</pre>
This is called in the graphics thread when a window is created.
It must make any calls needed to initialize graphics in the window.
<pre>
    void app_graphics_resize(int x, int y);
</pre>
Called when the window size changes.

<pre>
    void app_graphics_reread_prefs();
</pre>
This is called, in the graphics thread, whenever
the user's project preferences change.
It can call
".html_text("
    boinc_parse_init_data_file();
    boinc_get_init_data(APP_INIT_DATA&);
")."
to get the new preferences.

<p>
The application must supply the following input-handling functions:
<pre>
void boinc_app_mouse_move(
    int x, int y,       // new coords of cursor
    bool left,          // whether left mouse button is down
    bool middle,
    bool right
);

void boinc_app_mouse_button(
    int x, int y,       // coords of cursor
    int which,          // which button (0/1/2)
    bool is_down        // true iff button is now down
);

void boinc_app_key_press(
    int, int            // system-specific key encodings
)

void boinc_app_key_release(
    int, int            // system-specific key encodings
)
</pre>
<h3>Limiting frame rate</h3>
<p>
The following global variables control frame rate:
<p>
<b>boinc_max_fps</b> is an upper bound on the number of frames per second
(default 30).
<p>
<b>boinc_max_gfx_cpu_frac</b> is an upper bound on the fraction
of CPU time used for graphics (default 0.5).

<h3>Support classes</h3>
<p>
Several graphics-related classes were developed for SETI@home.
They may be of general utility.

<dl>
<dt>
REDUCED_ARRAY
<dd>
Represents a two-dimensional array of data,
which is reduced to a smaller dimension by averaging or taking extrema.
Includes member functions for drawing the reduced data as a 3D graph
in several ways (lines, rectangles, connected surface).
<dt>
PROGRESS and PROGRESS_2D
<dd>
Represent progress bars, depicted in 3 or 2 dimensions.

<dt>
RIBBON_GRAPH
<dd>
Represents of 3D graph of a function of 1 variable.

<dt>
MOVING_TEXT_PANEL
<dd>
Represents a flanged 3D panel, moving cyclically in 3 dimentions,
on which text is displayed.
<dt>
STARFIELD
<dd>
Represents a set of randomly-generated stars
that move forwards or backwards in 3 dimensions.

<dt>
TEXTURE_DESC
<dd>
Represents an image (JPEG, Targa, BMP, PNG, or RGB)
displayed in 3 dimensions.
</dl>
<p>
The file api/txf_util.C has support functions from
drawing nice-looking 3D text.

<h3>Static graphics</h3>
<p>
An application can display a pre-existing image file
(JPEG, GIFF, BMP or Targa) as its graphic.
This is the simplest approach since you
don't need to develop any code.
You must include the image file with each workunit.
To do this, link the application with api/static_graphics.C
(edit this file to use your filename).
You can change the image over time,
but you must change the (physical, not logical)
name of the file each time.
";
page_tail();
?>
