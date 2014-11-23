# Door Sign

An LCD sign to go on my door that displays what's currently happening in my calendar, called "Door Sign" because nobody who was sitting around me at the time had a better name.

![Photo](http://newfangled.me/images/door-sign.jpg)

## Hardware

You need:

* [Spark Core](http://spark.io) - £25
* [20x4 LCD](http://www.ebay.co.uk/itm/IIC-I2C-TWI-SP-I-Serial-Interface2004-20X4-Character-LCD-Module-Display-Blue-AR-/191314647477?pt=UK_BOI_Electrical_Components_Supplies_ET&hash=item2c8b3dd9b5) (others [here](http://www.ebay.co.uk/sch/i.html?_from=R40&_trksid=p2047675.m570.l1313.TR0.TRC0.H0.X20x4+lcd+i2c+serial&_nkw=20x4+lcd+i2c+serial&_sacat=0)) - £7
* [5V Regulator](http://www.ebay.co.uk/itm/L7805CV-Voltage-Regulator-5V-Pack-of-10-/390423690236?pt=UK_BOI_Electrical_Components_Supplies_ET&hash=item5ae710bbfc) - £2.39 for 10
* Some breadboard wires

Wire it up like:

![Breadboard](http://i.imgur.com/GKMMska.png)

## Firmware

Make a new project in the Spark online IDE named whatever you want, then copy in the contents of `door-sign.ino`. Click the + button in the tab bar of the IDE, and add a .h and .cpp file for the LiquidCrystal library.

Then flash it to the Spark with the little lightning bolt button.

## Software

Put all the code on a Heroku thing.

Obtain a Google Client ID and Secret:

1. Go to the (Google Developers Console)[https://console.developers.google.com/].
2. Select a project, or create a new one.
3. In the sidebar on the left, expand APIs & auth. Next, click APIs. In the list of APIs, make sure the status is ON for the Calendar API.
4. In the sidebar on the left, select Credentials.
5. In either case, you end up on the Credentials page and can create your project's credentials from here.
6. If you haven't done so already, create your OAuth 2.0 credentials by clicking Create new Client ID under the OAuth heading. Use the "Installed Application" option, with "Other" as the platform. Next, look for your application's client ID and client secret in the relevant table. You may also create and edit redirect URIs from this page.

__Add your config__:

    heroku config:set CLIENT_ID="abc" CLIENT_SECRET="def" SPARK_ID="mysparkid" SPARK_TOKEN="mysparktoken"

Spark ID is the device ID for your core that can be found in the IDE by clicking the target symbol in the bottom left and then the arrow next to your core. Your Spark token can be found in the settings page of your Spark IDE.

<b>Next, find your calendar IDs</b>

1. Visit (Google Calendar)[https://www.google.com/calendar/] in your web browser.
2. In the calendar list on the left, click the down-arrow button next to the appropriate calendar, then select Calendar settings.
3. In the Calendar Address section, locate the Calendar ID listed next to the XML, ICAL and HTML buttons.
4. Copy the Calendar ID.

Edit `bin/door-sign` and add the IDs and each calendar's friendly name.

Next, you need to obtain an access token (refresh token). To do so, run this command and follow the instructions:

    heroku run bundle exec ruby bin/authorize

Then add a scheduler to run the update script:

    heroku addons:add scheduler

Then set it up to run this command every ten minutes:

    bundle exec ruby bin/door-sign

Then stick the sign on your door and be happy.
