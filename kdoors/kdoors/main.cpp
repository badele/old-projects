
#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "kdoors.h"

static const char *description =
	I18N_NOOP("KDoors");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	
static KCmdLineOptions options[] =
{
  { "+[File]", I18N_NOOP("file to open"), 0 },
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};

int main(int argc, char *argv[])
{

	KAboutData aboutData( "kdoors", I18N_NOOP("KDoors"),
		VERSION, description, KAboutData::License_GPL,
		"(c) 2000, Bruno Adele");
	aboutData.addAuthor("Bruno Adele",0, "b_adele@netcourrier.com");
	aboutData.addCredit("Bruno Adele","Initiateur du projet", "b_adele@netcourrier.com","http://www.jesuislibre.org");
	KCmdLineArgs::init( argc, argv, &aboutData );
	KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

  KApplication app;
 
  if (app.isRestored())
  {
    RESTORE(KDoorsApp);
  }
  else 
  {
    KDoorsApp *kdoors = new KDoorsApp();
    kdoors->show();

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
		
		if (args->count())
		{
        kdoors->openDocumentFile(args->arg(0));
		}
/*		else
		{
		  kdoors->openDocumentFile();
		}*/
		args->clear();
  }

  return app.exec();
}  
