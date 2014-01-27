static void
test_calendar_escaping (void)
{
	GDataCalendarCalendar *calendar;

	calendar = gdata_calendar_calendar_new (NULL);
	gdata_calendar_calendar_set_timezone (calendar, "<timezone>");

	/* Check the outputted XML is escaped properly */
	gdata_test_assert_xml (calendar,
		"<?xml version='1.0' encoding='UTF-8'?>"
		"<entry xmlns='http://www.w3.org/2005/Atom' xmlns:gd='http://schemas.google.com/g/2005' "
		       "xmlns:gCal='http://schemas.google.com/gCal/2005' xmlns:app='http://www.w3.org/2007/app'>"
			"<title type='text'></title>"
			"<category term='http://schemas.google.com/gCal/2005#calendarmeta' scheme='http://schemas.google.com/g/2005#kind'/>"
			"<gCal:timezone value='&lt;timezone&gt;'/>"
			"<gCal:hidden value='false'/>"
			"<gCal:color value='#000000'/>"
			"<gCal:selected value='false'/>"
		"</entry>");
	g_object_unref (calendar);
}




//For gdata_json_test
g_assert_no_error (error);
	g_assert (GDATA_IS_ENTRY (event));
	g_clear_error (&error);
        fflush(NULL);

	i = gdata_calendar_event_get_times (event);
        printf("\n No error");

	when = GDATA_GD_WHEN (i->data);
	printf("is_date is %d", gdata_gd_when_is_date(when));
	_time = gdata_gd_when_get_start_time (when);
        printf("start time is %ld", _time);
	_time = gdata_gd_when_get_end_time (when);
        printf("end time is %ld", _time);
        fflush(NULL);
        
        GList* reminder_list = gdata_gd_when_get_reminders(when);
        GDataGDReminder *reminder;
        while(reminder_list != NULL){
            reminder = GDATA_GD_REMINDER(reminder_list->data);
            printf("is_absolute_time is %d", gdata_gd_reminder_is_absolute_time(reminder));
            printf("method is %s", gdata_gd_reminder_get_method(reminder));
            printf("time is %ld", gdata_gd_reminder_get_relative_time(reminder));
            printf("\n");
            fflush(NULL);
            reminder_list = reminder_list->next;
        }
        
        GList* who_list = gdata_calendar_event_get_people(event);
        GDataGDWho *who;
        while(who_list != NULL){
            who = GDATA_GD_WHO(who_list->data);
            printf("\n");
            printf("The email is %s ", gdata_gd_who_get_email_address(who));
            printf("THe display name is %s ", gdata_gd_who_get_value_string(who));
            //printf("is optional? %d ", gdata_gd_who_get_optional(who));
            //printf("response status is %s ", gdata_gd_who_get_response_status(who));
            printf("\n");
            fflush(NULL);
            who_list = who_list->next;
        }
        
        printf("\n The recurrence is %s \n", gdata_calendar_event_get_recurrence(event));
	fflush(NULL);

        
        //TEST example
        "{\"kind\": \"calendar#event\","
                "\"etag\": \"\\\"riS6FXjHtObfGZnFmNP8yHjrZcU/MTM3ODMwNzk1NzIyNjAwMA\\\"\","
                "\"id\": \"kcbn6pik8tco9tds1hofbbj1m8\","
                "\"status\": \"confirmed\","
                "\"htmlLink\": \"https://www.google.com/calendar/event?eid=a2NibjZwaWs4dGNvOXRkczFob2ZiYmoxbThfMjAxMzA5MDVUMTIzMDAwWiB3aWxsLm15dUBt\","
                "\"created\": \"2013-09-04T15:18:53.000Z\","
                "\"updated\": \"2013-09-04T15:19:17.226Z\","
                "\"summary\": \"Physical Electronics \","
                "\"location\": \"1255 Anthony Hall \","
                "\"colorId\": \"10\","
                "\"creator\": {"
                "\"email\": \"will.myu@gmail.com\","
                "\"displayName\": \"Miao Yu\","
                "\"self\": true"
                "},"
                "\"organizer\": {"
                "\"email\": \"will.myu@gmail.com\","
                "\"displayName\": \"Miao Yu\","
                "\"self\": true"
                "},"
                "\"start\": {"
                "\"dateTime\": \"2013-09-05T08:30:00-04:00\","
                "\"timeZone\": \"America/New_York\""
                "},"
                "\"end\": {"
                "\"dateTime\": \"2013-09-05T09:50:00-04:00\","
                "\"timeZone\": \"America/New_York\""
                "},"
                "\"recurrence\": ["
                "\"RRULE:FREQ=WEEKLY;BYDAY=TU,TH\""
                "],"
                "\"iCalUID\": \"kcbn6pik8tco9tds1hofbbj1m8@google.com\","
                "\"sequence\": 0,"
                "\"reminders\": {"
                "\"useDefault\": true}}"