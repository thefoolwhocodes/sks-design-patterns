/*
	The program demonstrates the following:
	Facade:
		-> Provide a unified interface to a set of interfaces in a subsystem.
		-> It defines a higher-level interface that makes the subsystem easier to use.

	Applicability:
		-> You want to provide a simple interface to a complex subsystem.
		-> Introduce a facade to decouple the subsystem from clients and other subsystems, thereby promoting
			subsystem independence and portability.
		-> You want to layer your subsystems. Use a facade to define an entry
			point to each subsystem level.

	Participants:
		(a).Facade:
			-> Knows which subsystem classes are responsible for a request.
			-> Delegates client requests to appropriate subsystem objects.
		(b).Subsystem classes:
			-> Implement subsystem functionality.
			-> Handle work assigned by the Facade object.
			-> Have no knowledge of the facade; that is, they keep no references to it.

	How it is achieved:
		-> Clients communicate with the subsystem by sending requests to Facade, which forwards them to the appropriate subsystem object(s).
		-> The facade may have to do work of its own to translate its interface to subsystem interfaces.
		-> Clients that use the facade don't have to access its subsystem objects directly.

	Consequences:
		-> It shields clients from subsystem components, thereby reducing the number of objects that clients deal with and making the subsystem
			easier to use.
		-> It promotes weak coupling between the subsystem and its clients.
		-> It doesn't prevent applications from using subsystem classes if they need to.


	Implementation(Things to be considered):
		-> Reducing client-subsystem coupling.
		-> Public versus private subsystem classes.

	Example:
		-> Compiler
*/

#include <iostream>

namespace Demo1
{
	//Subsystem 1
	class MisDepartment
	{
		public:
		void submitNetworkRequest()
		{
			_state = 0;
		}
		bool checkOnStatus()
		{
			_state++;
			if (_state == Complete)
			{
				return 1;
			}
			return 0;
		}
		private:
		enum States
		{
			Received,
			DenyAllKnowledge,
			ReferClientToFacilities,
			FacilitiesHasNotSentPaperwork,
			ElectricianIsNotDone,
			ElectricianDidItWrong,
			DispatchTechnician,
			SignedOff,
			DoesNotWork,
			FixElectriciansWiring,
			Complete
		};
		int _state;
	};

	//Subsystem 2
	class ElectricianUnion
	{
		public:
		void submitNetworkRequest()
		{
			_state = 0;
		}
		bool checkOnStatus()
		{
			_state++;
			if (_state == Complete)
			{
				return 1;
			}
			return 0;
		}
		private:
		enum States
		{
			Received,
			RejectTheForm,
			SizeTheJob,
			SmokeAndJokeBreak,
			WaitForAuthorization,
			DoTheWrongJob,
			BlameTheEngineer,
			WaitToPunchOut,
			DoHalfAJob,
			ComplainToEngineer,
			GetClarification,
			CompleteTheJob,
			TurnInThePaperwork,
			Complete
		};
		int _state;
	};

	//Subsystem 3
	class FacilitiesDepartment
	{
		public:
		void submitNetworkRequest()
		{
			_state = 0;
		}
		bool checkOnStatus()
		{
			_state++;
			if (_state == Complete)
			{
				return 1;
			}
			return 0;
		}
		private:
		enum States
		{
			Received,
			AssignToEngineer,
			EngineerResearches,
			RequestIsNotPossible,
			EngineerLeavesCompany,
			AssignToNewEngineer,
			NewEngineerResearches,
			ReassignEngineer,
			EngineerReturns,
			EngineerResearchesAgain,
			EngineerFillsOutPaperWork,
			Complete
		};
		int _state;
	};

	//Facade
	class FacilitiesFacade
	{
		public:
		FacilitiesFacade()
		{
			_count = 0;
		}
		void submitNetworkRequest()
		{
			_state = 0;
		}
		bool checkOnStatus()
		{
			_count++;
			/* Job request has just been received */
			if (_state == Received)
			{
				_state++;
				/* Forward the job request to the engineer */
				_engineer.submitNetworkRequest();
				std::cout << "submitted to Facilities - " << _count <<" phone calls so far" << std::endl;
			}
			else if (_state == SubmitToEngineer)
			{
				/* If engineer is complete, forward to electrician */
				if (_engineer.checkOnStatus())
				{
					_state++;
					_electrician.submitNetworkRequest();
					std::cout << "submitted to Electrician - " << _count <<" phone calls so far" << std::endl;
				}
			}
			else if (_state == SubmitToElectrician)
			{
				/* If electrician is complete, forward to technician */
				if (_electrician.checkOnStatus())
				{
					_state++;
					_technician.submitNetworkRequest();
					std::cout << "submitted to MIS - " << _count <<" phone calls so far" << std::endl;
				}
			}
			else if (_state == SubmitToTechnician)
			{
				/* If technician is complete, job is done */
				if (_technician.checkOnStatus())
				return 1;
			}
			/* The job is not entirely complete */
			return 0;
		}

		int getNumberOfCalls()
		{
			return _count;
		}

		private:
		enum States
		{
			Received,
			SubmitToEngineer,
			SubmitToElectrician,
			SubmitToTechnician
		};
		int _state;
		int _count;
		FacilitiesDepartment _engineer;
		ElectricianUnion _electrician;
		MisDepartment _technician;
	};
};

int main()
{
	{
		std::cout<<"Start of Demo1"<<std::endl;

		Demo1::FacilitiesFacade facilities;
		facilities.submitNetworkRequest();

		/* Keep checking until job is complete */
		while (!facilities.checkOnStatus());
		std::cout << "job completed after only " << facilities.getNumberOfCalls() << " phone calls" << std::endl;

		std::cout<<"End of Demo1"<<std::endl;
	}
	return 0;
}
