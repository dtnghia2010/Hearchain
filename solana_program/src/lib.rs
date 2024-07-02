use borsh::{BorshDeserialize, BorshSerialize};
use solana_program::{
    account_info::{next_account_info, AccountInfo},
    entrypoint,
    entrypoint::ProgramResult,
    msg,
    pubkey::Pubkey,
};

// Define the instruction data structure
#[derive(BorshSerialize, BorshDeserialize, Debug)]
pub struct InstructionData {
    pub patient_id: String,
    pub ecg_data: Vec<u8>,
}

// Define the program entrypoint
entrypoint!(process_instruction);

pub fn process_instruction(
    program_id: &Pubkey,
    accounts: &[AccountInfo],
    instruction_data: &[u8],
) -> ProgramResult {
    let accounts_iter = &mut accounts.iter();

    // Get the account to modify
    let account = next_account_info(accounts_iter)?;

    // Deserialize instruction data
    let instruction = InstructionData::try_from_slice(instruction_data)?;

    // Log the instruction data
    msg!("Received ECG data for patient: {:?}", instruction.patient_id);

    // Store the ECG data in the account's data
    let mut account_data = account.data.borrow_mut();
    account_data[..instruction.ecg_data.len()].copy_from_slice(&instruction.ecg_data);

    Ok(())
}
